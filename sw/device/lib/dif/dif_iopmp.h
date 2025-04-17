// Copyright lowRISC contributors (OpenTitan project).
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0



#ifndef OPENTITAN_SW_DEVICE_LIB_DIF_DIF_IOPMP_H_
#define OPENTITAN_SW_DEVICE_LIB_DIF_DIF_IOPMP_H_

/**
 * @file
 * @brief <a href="/book/hw/ip/iopmp/">IOPMP</a> Device Interface Functions
 */

#include <stdint.h>

#include "sw/device/lib/dif/autogen/dif_iopmp_autogen.h"

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

/**
 * Runtime configuration for IOPMP.
 *
 * This struct describes (SOFTWARE) runtime information for one-time
 * configuration of the hardware.
 */
typedef struct dif_iopmp_config {
  uint8_t unused;
} dif_iopmp_config_t;


/**
 * Parameters for a IOPMP transaction.
 */
typedef struct dif_iopmp_transaction {
  uint8_t unused;
} dif_iopmp_transaction_t;

/**
 * An output location for a IOPMP transaction.
 */
typedef struct dif_iopmp_output {
  uint8_t unused;
} dif_iopmp_output_t;

/**
 * Configures IOPMP with runtime information.
 *
 * This function should only need to be called once for the lifetime of
 * `handle`.
 *
 * @param iopmp A IOPMP handle.
 * @param config Runtime configuration parameters.
 * @return The result of the operation.
 */
OT_WARN_UNUSED_RESULT
dif_result_t dif_iopmp_configure(
  const dif_iopmp_t *iopmp,
  dif_iopmp_config_t config);

/**
 * Begins a IOPMP transaction.
 *
 * Each call to this function should be sequenced with a call to
 * `dif_iopmp_end()`.
 *
 * @param iopmp A IOPMP handle.
 * @param transaction Transaction configuration parameters.
 * @return The result of the operation.
 */
OT_WARN_UNUSED_RESULT
dif_result_t dif_iopmp_start(
  const dif_iopmp_t *iopmp,
  dif_iopmp_transaction_t transaction);

/** Ends a IOPMP transaction, writing the results to the given output.
 *
 * @param iopmp A IOPMP handle.
 * @param output Transaction output parameters.
 * @return The result of the operation.
 */
OT_WARN_UNUSED_RESULT
dif_result_t dif_iopmp_end(
  const dif_iopmp_t *iopmp,
  dif_iopmp_output_t output);

/**
 * Locks out IOPMP functionality.
 *
 * This function is reentrant: calling it while functionality is locked will
 * have no effect and return `kDifOk`.
 *
 * @param iopmp A IOPMP handle.
 * @return The result of the operation.
 */
OT_WARN_UNUSED_RESULT
dif_result_t dif_iopmp_lock(
  const dif_iopmp_t *iopmp);

/**
 * Checks whether this IOPMP is locked.
 *
 * @param iopmp A IOPMP handle.
 * @param[out] is_locked Out-param for the locked state.
 * @return The result of the operation.
 */
OT_WARN_UNUSED_RESULT
dif_result_t dif_iopmp_is_locked(
  const dif_iopmp_t *iopmp,
  bool *is_locked);

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

#endif  // OPENTITAN_SW_DEVICE_LIB_DIF_DIF_IOPMP_H_
