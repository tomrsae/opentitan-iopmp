// Copyright lowRISC contributors (OpenTitan project).
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#ifndef OPENTITAN_SW_DEVICE_LIB_TESTING_AUTOGEN_ISR_TESTUTILS_H_
#define OPENTITAN_SW_DEVICE_LIB_TESTING_AUTOGEN_ISR_TESTUTILS_H_

// THIS FILE HAS BEEN GENERATED, DO NOT EDIT MANUALLY. COMMAND:
// util/autogen_testutils.py

/**
 * @file
 * @brief Default ISRs for each IP
 */

#include "sw/device/lib/dif/dif_iopmp.h"
#include "sw/device/lib/dif/dif_rv_plic.h"

#include "hw/top_earlgrey/sw/autogen/top_earlgrey.h"  // Generated.

/**
 * A handle to a PLIC ISR context struct.
 */
typedef struct plic_isr_ctx {
  /**
   * A handle to a rv_plic.
   */
  dif_rv_plic_t *rv_plic;
  /**
   * The HART ID associated with the PLIC (correspond to a PLIC "target").
   */
  uint32_t hart_id;
} plic_isr_ctx_t;

/**
 * A handle to a iopmp ISR context struct.
 */
typedef struct iopmp_isr_ctx {
  /**
   * A handle to a iopmp.
   */
  dif_iopmp_t *iopmp;
  /**
   * The PLIC IRQ ID where this iopmp instance's IRQs start.
   */
  dif_rv_plic_irq_id_t plic_iopmp_start_irq_id;
  /**
   * The iopmp IRQ that is expected to be encountered in the ISR.
   */
  dif_iopmp_irq_t expected_irq;
  /**
   * Whether or not a single IRQ is expected to be encountered in the ISR.
   */
  bool is_only_irq;
} iopmp_isr_ctx_t;

/**
 * Services an iopmp IRQ.
 *
 * @param plic_ctx A PLIC ISR context handle.
 * @param iopmp_ctx A(n) iopmp ISR context handle.
 * @param[out] peripheral_serviced Out param for the peripheral that was
 * serviced.
 * @param[out] irq_serviced Out param for the IRQ that was serviced.
 */
void isr_testutils_iopmp_isr(
    plic_isr_ctx_t plic_ctx, iopmp_isr_ctx_t iopmp_ctx,
    top_earlgrey_plic_peripheral_t *peripheral_serviced,
    dif_iopmp_irq_t *irq_serviced);

#endif  // OPENTITAN_SW_DEVICE_LIB_TESTING_AUTOGEN_ISR_TESTUTILS_H_
