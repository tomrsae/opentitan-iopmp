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

  const ptrdiff_t entry1_addr = 0x0000ffffu;
  const ptrdiff_t entry2_addr = 0x0001ffffu;
  const ptrdiff_t entry3_addr = 0x0002ffffu;
  const ptrdiff_t entry4_addr = 0x0003ffffu;
  const ptrdiff_t entry5_addr = 0x0004ffffu;
  const ptrdiff_t entry6_addr = 0x0005ffffu;
  const ptrdiff_t entry7_addr = 0x0006ffffu;

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
  // | RRID_00001 | MD_002     | Example entry 5             |
  // |            |            | Example entry 6             |
  // +------------+------------+-----------------------------+

  // add all entries

  dif_iopmp_add_entry(&iopmp, entry1_addr, &entry_cfg);
  dif_iopmp_add_entry(&iopmp, entry2_addr, &entry_cfg);
  dif_iopmp_add_entry(&iopmp, entry3_addr, &entry_cfg);
  dif_iopmp_add_entry(&iopmp, entry4_addr, &entry_cfg);
  dif_iopmp_add_entry(&iopmp, entry5_addr, &entry_cfg);
  dif_iopmp_add_entry(&iopmp, entry6_addr, &entry_cfg);
  dif_iopmp_add_entry(&iopmp, entry7_addr, &entry_cfg);

  // configure what entries belong to what MDs

  // MDCFG(0).t = 3 ==> MD 0 has entry 0, 1, 2
  dif_iopmp_mdcfg_set_top_range(&iopmp, 0, 3);
  // MDCFG(0).t = 3 & MDCFG(1).t = 5 ==> MD 1 has entry 3, 4
  dif_iopmp_mdcfg_set_top_range(&iopmp, 1, 5);
  // MDCFG(1).t = 5 & MDCFG(2).t = 7 ==> MD 2 has entry 5, 6
  dif_iopmp_mdcfg_set_top_range(&iopmp, 2, 7);

  // assign RRIDs to MDs

  dif_iopmp_md_mask_for_rrid(&iopmp, 0, 3, true); // 3 = 0b0011 ==> first two MDs, with lock
  dif_iopmp_md_mask_for_rrid(&iopmp, 1, 4, false); // 4 = 0b0100 ==> third MD, no lock

  return true;
}
