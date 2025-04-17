#include <string.h>

#include "sw/device/lib/arch/device.h"
#include "sw/device/lib/base/mmio.h"
#include "sw/device/lib/dif/dif_iopmp.h"
#include "sw/device/lib/runtime/hart.h"

#include "sw/device/lib/testing/test_framework/ottf_main.h"
#include "sw/device/lib/testing/test_framework/check.h"
#include "sw/device/lib/runtime/log.h"

#include "hw/top_earlgrey/sw/autogen/top_earlgrey.h"

// INFO registers
#define IOPMP_VERSION_REG_OFFSET 0x0000
#define IOPMP_IMPLEMENTATION_REG_OFFSET 0x0004

OTTF_DEFINE_TEST_CONFIG();

bool test_main(void) {
  LOG_INFO("IOPMP test running!");

  dif_iopmp_t iopmp;
  CHECK_DIF_OK(dif_iopmp_init(
      mmio_region_from_addr(TOP_EARLGREY_IOPMP_CFG_BASE_ADDR), &iopmp));

  test_status_set(kTestStatusPassed);

  return true;
}
