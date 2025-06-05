#include "sw/device/lib/arch/device.h"
#include "sw/device/lib/base/mmio.h"
#include "sw/device/lib/dif/dif_iopmp.h"
#include "sw/device/lib/runtime/hart.h"

#include "sw/device/lib/testing/test_framework/ottf_main.h"
#include "sw/device/lib/testing/test_framework/check.h"
#include "sw/device/lib/runtime/log.h"

#include "hw/top_earlgrey/sw/autogen/top_earlgrey.h"

OTTF_DEFINE_TEST_CONFIG();

bool test_main(void) {
  LOG_INFO("IOPMP test running");

  dif_iopmp_t iopmp;
  CHECK_DIF_OK(dif_iopmp_init(
      mmio_region_from_addr(TOP_EARLGREY_IOPMP_CFG_BASE_ADDR), &iopmp));

  dif_iopmp_config_t iopmp_cfg;
  dif_iopmp_get_config(&iopmp, &iopmp_cfg);
  
  LOG_INFO("Entry offset: 0x%08x", iopmp_cfg.entryoffset);

  const ptrdiff_t entry0_addr = 0x0000ffffu;
  const ptrdiff_t entry1_addr = 0x0001ffffu;
  const ptrdiff_t entry2_addr = 0x0002ffffu;
  const ptrdiff_t entry3_addr = 0x0003ffffu;
  const ptrdiff_t entry4_addr = 0x0004ffffu;
  const ptrdiff_t entry5_addr = 0x0005ffffu;

  // common config for test simplicity
  dif_iopmp_entry_cfg_t entry_cfg = {
    .r = kDifToggleEnabled,
    .w = kDifToggleEnabled,
    .x = kDifToggleEnabled,
    .a = kDifIopmpEntryAddrModeOff,
    .sire = kDifToggleDisabled,
    .siwe = kDifToggleDisabled,
    .sixe = kDifToggleDisabled,
    .sere = kDifToggleDisabled,
    .sewe = kDifToggleDisabled,
    .sexe = kDifToggleDisabled
  };

  // +------------+------------+-----------------------------+
  // |   RRID     |    MD      |           Entry             |
  // +------------+------------+-----------------------------+
  // | RRID_00000 | MD_000     | Example entry 0             |
  // |            |            | Example entry 1             |
  // |            |            | Example entry 2             |
  // +            +------------+-----------------------------+
  // |            | MD_001     | Example entry 3             |
  // |            |            | Example entry 4             |
  // +------------+------------+-----------------------------+

  // add all entries

  dif_iopmp_add_entry(&iopmp, &iopmp_cfg, entry0_addr, &entry_cfg);
  dif_iopmp_add_entry(&iopmp, &iopmp_cfg, entry1_addr, &entry_cfg);
  dif_iopmp_add_entry(&iopmp, &iopmp_cfg, entry2_addr, &entry_cfg);
  dif_iopmp_add_entry(&iopmp, &iopmp_cfg, entry3_addr, &entry_cfg);
  dif_iopmp_add_entry(&iopmp, &iopmp_cfg, entry4_addr, &entry_cfg);
  dif_iopmp_add_entry(&iopmp, &iopmp_cfg, entry5_addr, &entry_cfg);

  // configure what entries belong to what MDs, using mdcfg's top range

  // MDCFG(0).t = 3 ==> MD 0 has entry 0, 1, 2
  uint32_t md0_top_range = 3;
  dif_iopmp_mdcfg_set_top_range(&iopmp, 0, md0_top_range);
  // MDCFG(0).t = 3 & MDCFG(1).t = 5 ==> MD 1 has entry 3, 4
  uint32_t md1_top_range = 5;
  dif_iopmp_mdcfg_set_top_range(&iopmp, 1, md1_top_range);

  // assign RRIDs to MDs
  uint32_t rrid = 0;
  uint32_t md_mask = 3; // 3 = 0b0011 ==> first two MDs
  bool md_mask_lock = true;
  dif_iopmp_set_md_mask_for_rrid(&iopmp, rrid, md_mask, md_mask_lock);

  // verify that written values can be read back out

  // verify that entries are equal
  dif_iopmp_entry_cfg_t read_entry_cfg;
  uint32_t read_entry_addr = 0;

  dif_iopmp_get_entry(&iopmp, &iopmp_cfg, 0, &read_entry_addr, &read_entry_cfg);
  CHECK(entry0_addr == read_entry_addr);
  CHECK(dif_iopmp_cmp_entry_cfg(&entry_cfg, &read_entry_cfg));

  dif_iopmp_get_entry(&iopmp, &iopmp_cfg, 1, &read_entry_addr, &read_entry_cfg);
  CHECK(entry1_addr == read_entry_addr);
  CHECK(dif_iopmp_cmp_entry_cfg(&entry_cfg, &read_entry_cfg));

  dif_iopmp_get_entry(&iopmp, &iopmp_cfg, 2, &read_entry_addr, &read_entry_cfg);
  CHECK(entry2_addr == read_entry_addr);
  CHECK(dif_iopmp_cmp_entry_cfg(&entry_cfg, &read_entry_cfg));

  dif_iopmp_get_entry(&iopmp, &iopmp_cfg, 3, &read_entry_addr, &read_entry_cfg);
  CHECK(entry3_addr == read_entry_addr);
  CHECK(dif_iopmp_cmp_entry_cfg(&entry_cfg, &read_entry_cfg));

  dif_iopmp_get_entry(&iopmp, &iopmp_cfg, 4, &read_entry_addr, &read_entry_cfg);
  CHECK(entry4_addr == read_entry_addr);
  CHECK(dif_iopmp_cmp_entry_cfg(&entry_cfg, &read_entry_cfg));

  dif_iopmp_get_entry(&iopmp, &iopmp_cfg, 5, &read_entry_addr, &read_entry_cfg);
  CHECK(entry5_addr == read_entry_addr);
  CHECK(dif_iopmp_cmp_entry_cfg(&entry_cfg, &read_entry_cfg));

  // verify MD top ranges
  uint32_t read_top_range = 0;

  dif_iopmp_mdcfg_get_top_range(&iopmp, 0, &read_top_range);
  CHECK(md0_top_range == read_top_range);

  dif_iopmp_mdcfg_get_top_range(&iopmp, 1, &read_top_range);
  CHECK(md1_top_range == read_top_range);

  // verify that MD belongs to expected rrid
  uint32_t read_md_mask = 0;
  bool read_md_mask_lock;

  dif_iopmp_get_md_mask_for_rrid(&iopmp, rrid, &read_md_mask, &read_md_mask_lock);
  CHECK(md_mask == read_md_mask);
  CHECK(md_mask_lock == read_md_mask_lock);

  return true;
}
