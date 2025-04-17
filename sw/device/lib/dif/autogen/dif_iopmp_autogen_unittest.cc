// Copyright lowRISC contributors (OpenTitan project).
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

// THIS FILE HAS BEEN GENERATED, DO NOT EDIT MANUALLY. COMMAND:
// util/make_new_dif.py --mode=regen --only=autogen

#include "sw/device/lib/dif/autogen/dif_iopmp_autogen.h"

#include "gtest/gtest.h"
#include "sw/device/lib/base/mmio.h"
#include "sw/device/lib/base/mock_mmio.h"
#include "sw/device/lib/dif/dif_test_base.h"

#include "iopmp_regs.h"  // Generated.

namespace dif_iopmp_autogen_unittest {
namespace {
using ::mock_mmio::MmioTest;
using ::mock_mmio::MockDevice;
using ::testing::Eq;
using ::testing::Test;

class IopmpTest : public Test, public MmioTest {
 protected:
  dif_iopmp_t iopmp_ = {.base_addr = dev().region()};
};

class InitTest : public IopmpTest {};

TEST_F(InitTest, NullArgs) {
  EXPECT_DIF_BADARG(dif_iopmp_init(dev().region(), nullptr));
}

TEST_F(InitTest, Success) {
  EXPECT_DIF_OK(dif_iopmp_init(dev().region(), &iopmp_));
}

class IrqGetTypeTest : public IopmpTest {};

TEST_F(IrqGetTypeTest, NullArgs) {
  dif_irq_type_t type;

  EXPECT_DIF_BADARG(
      dif_iopmp_irq_get_type(nullptr, kDifIopmpIrqAccessViolation, &type));

  EXPECT_DIF_BADARG(
      dif_iopmp_irq_get_type(&iopmp_, kDifIopmpIrqAccessViolation, nullptr));

  EXPECT_DIF_BADARG(
      dif_iopmp_irq_get_type(nullptr, kDifIopmpIrqAccessViolation, nullptr));
}

TEST_F(IrqGetTypeTest, BadIrq) {
  dif_irq_type_t type;

  EXPECT_DIF_BADARG(dif_iopmp_irq_get_type(
      &iopmp_, static_cast<dif_iopmp_irq_t>(kDifIopmpIrqAccessViolation + 1),
      &type));
}

TEST_F(IrqGetTypeTest, Success) {
  dif_irq_type_t type;

  EXPECT_DIF_OK(
      dif_iopmp_irq_get_type(&iopmp_, kDifIopmpIrqAccessViolation, &type));
  EXPECT_EQ(type, kDifIrqTypeEvent);
}

class IrqGetStateTest : public IopmpTest {};

TEST_F(IrqGetStateTest, NullArgs) {
  dif_iopmp_irq_state_snapshot_t irq_snapshot = 0;

  EXPECT_DIF_BADARG(dif_iopmp_irq_get_state(nullptr, &irq_snapshot));

  EXPECT_DIF_BADARG(dif_iopmp_irq_get_state(&iopmp_, nullptr));

  EXPECT_DIF_BADARG(dif_iopmp_irq_get_state(nullptr, nullptr));
}

TEST_F(IrqGetStateTest, SuccessAllRaised) {
  dif_iopmp_irq_state_snapshot_t irq_snapshot = 0;

  EXPECT_READ32(IOPMP_INTR_STATE_REG_OFFSET,
                std::numeric_limits<uint32_t>::max());
  EXPECT_DIF_OK(dif_iopmp_irq_get_state(&iopmp_, &irq_snapshot));
  EXPECT_EQ(irq_snapshot, std::numeric_limits<uint32_t>::max());
}

TEST_F(IrqGetStateTest, SuccessNoneRaised) {
  dif_iopmp_irq_state_snapshot_t irq_snapshot = 0;

  EXPECT_READ32(IOPMP_INTR_STATE_REG_OFFSET, 0);
  EXPECT_DIF_OK(dif_iopmp_irq_get_state(&iopmp_, &irq_snapshot));
  EXPECT_EQ(irq_snapshot, 0);
}

class IrqIsPendingTest : public IopmpTest {};

TEST_F(IrqIsPendingTest, NullArgs) {
  bool is_pending;

  EXPECT_DIF_BADARG(dif_iopmp_irq_is_pending(
      nullptr, kDifIopmpIrqAccessViolation, &is_pending));

  EXPECT_DIF_BADARG(
      dif_iopmp_irq_is_pending(&iopmp_, kDifIopmpIrqAccessViolation, nullptr));

  EXPECT_DIF_BADARG(
      dif_iopmp_irq_is_pending(nullptr, kDifIopmpIrqAccessViolation, nullptr));
}

TEST_F(IrqIsPendingTest, BadIrq) {
  bool is_pending;
  // All interrupt CSRs are 32 bit so interrupt 32 will be invalid.
  EXPECT_DIF_BADARG(dif_iopmp_irq_is_pending(
      &iopmp_, static_cast<dif_iopmp_irq_t>(32), &is_pending));
}

TEST_F(IrqIsPendingTest, Success) {
  bool irq_state;

  // Get the first IRQ state.
  irq_state = false;
  EXPECT_READ32(IOPMP_INTR_STATE_REG_OFFSET,
                {{IOPMP_INTR_STATE_ACCESS_VIOLATION_BIT, true}});
  EXPECT_DIF_OK(dif_iopmp_irq_is_pending(&iopmp_, kDifIopmpIrqAccessViolation,
                                         &irq_state));
  EXPECT_TRUE(irq_state);
}

class AcknowledgeStateTest : public IopmpTest {};

TEST_F(AcknowledgeStateTest, NullArgs) {
  dif_iopmp_irq_state_snapshot_t irq_snapshot = 0;
  EXPECT_DIF_BADARG(dif_iopmp_irq_acknowledge_state(nullptr, irq_snapshot));
}

TEST_F(AcknowledgeStateTest, AckSnapshot) {
  constexpr uint32_t num_irqs = 1;
  constexpr uint32_t irq_mask = (uint64_t{1} << num_irqs) - 1;
  dif_iopmp_irq_state_snapshot_t irq_snapshot = 1;

  // Test a few snapshots.
  for (size_t i = 0; i < num_irqs; ++i) {
    irq_snapshot = ~irq_snapshot & irq_mask;
    irq_snapshot |= (1u << i);
    EXPECT_WRITE32(IOPMP_INTR_STATE_REG_OFFSET, irq_snapshot);
    EXPECT_DIF_OK(dif_iopmp_irq_acknowledge_state(&iopmp_, irq_snapshot));
  }
}

TEST_F(AcknowledgeStateTest, SuccessNoneRaised) {
  dif_iopmp_irq_state_snapshot_t irq_snapshot = 0;

  EXPECT_READ32(IOPMP_INTR_STATE_REG_OFFSET, 0);
  EXPECT_DIF_OK(dif_iopmp_irq_get_state(&iopmp_, &irq_snapshot));
  EXPECT_EQ(irq_snapshot, 0);
}

class AcknowledgeAllTest : public IopmpTest {};

TEST_F(AcknowledgeAllTest, NullArgs) {
  EXPECT_DIF_BADARG(dif_iopmp_irq_acknowledge_all(nullptr));
}

TEST_F(AcknowledgeAllTest, Success) {
  EXPECT_WRITE32(IOPMP_INTR_STATE_REG_OFFSET,
                 std::numeric_limits<uint32_t>::max());

  EXPECT_DIF_OK(dif_iopmp_irq_acknowledge_all(&iopmp_));
}

class IrqAcknowledgeTest : public IopmpTest {};

TEST_F(IrqAcknowledgeTest, NullArgs) {
  EXPECT_DIF_BADARG(
      dif_iopmp_irq_acknowledge(nullptr, kDifIopmpIrqAccessViolation));
}

TEST_F(IrqAcknowledgeTest, BadIrq) {
  EXPECT_DIF_BADARG(
      dif_iopmp_irq_acknowledge(nullptr, static_cast<dif_iopmp_irq_t>(32)));
}

TEST_F(IrqAcknowledgeTest, Success) {
  // Clear the first IRQ state.
  EXPECT_WRITE32(IOPMP_INTR_STATE_REG_OFFSET,
                 {{IOPMP_INTR_STATE_ACCESS_VIOLATION_BIT, true}});
  EXPECT_DIF_OK(
      dif_iopmp_irq_acknowledge(&iopmp_, kDifIopmpIrqAccessViolation));
}

class IrqForceTest : public IopmpTest {};

TEST_F(IrqForceTest, NullArgs) {
  EXPECT_DIF_BADARG(
      dif_iopmp_irq_force(nullptr, kDifIopmpIrqAccessViolation, true));
}

TEST_F(IrqForceTest, BadIrq) {
  EXPECT_DIF_BADARG(
      dif_iopmp_irq_force(nullptr, static_cast<dif_iopmp_irq_t>(32), true));
}

TEST_F(IrqForceTest, Success) {
  // Force first IRQ.
  EXPECT_WRITE32(IOPMP_INTR_TEST_REG_OFFSET,
                 {{IOPMP_INTR_TEST_ACCESS_VIOLATION_BIT, true}});
  EXPECT_DIF_OK(
      dif_iopmp_irq_force(&iopmp_, kDifIopmpIrqAccessViolation, true));
}

class IrqGetEnabledTest : public IopmpTest {};

TEST_F(IrqGetEnabledTest, NullArgs) {
  dif_toggle_t irq_state;

  EXPECT_DIF_BADARG(dif_iopmp_irq_get_enabled(
      nullptr, kDifIopmpIrqAccessViolation, &irq_state));

  EXPECT_DIF_BADARG(
      dif_iopmp_irq_get_enabled(&iopmp_, kDifIopmpIrqAccessViolation, nullptr));

  EXPECT_DIF_BADARG(
      dif_iopmp_irq_get_enabled(nullptr, kDifIopmpIrqAccessViolation, nullptr));
}

TEST_F(IrqGetEnabledTest, BadIrq) {
  dif_toggle_t irq_state;

  EXPECT_DIF_BADARG(dif_iopmp_irq_get_enabled(
      &iopmp_, static_cast<dif_iopmp_irq_t>(32), &irq_state));
}

TEST_F(IrqGetEnabledTest, Success) {
  dif_toggle_t irq_state;

  // First IRQ is enabled.
  irq_state = kDifToggleDisabled;
  EXPECT_READ32(IOPMP_INTR_ENABLE_REG_OFFSET,
                {{IOPMP_INTR_ENABLE_ACCESS_VIOLATION_BIT, true}});
  EXPECT_DIF_OK(dif_iopmp_irq_get_enabled(&iopmp_, kDifIopmpIrqAccessViolation,
                                          &irq_state));
  EXPECT_EQ(irq_state, kDifToggleEnabled);
}

class IrqSetEnabledTest : public IopmpTest {};

TEST_F(IrqSetEnabledTest, NullArgs) {
  dif_toggle_t irq_state = kDifToggleEnabled;

  EXPECT_DIF_BADARG(dif_iopmp_irq_set_enabled(
      nullptr, kDifIopmpIrqAccessViolation, irq_state));
}

TEST_F(IrqSetEnabledTest, BadIrq) {
  dif_toggle_t irq_state = kDifToggleEnabled;

  EXPECT_DIF_BADARG(dif_iopmp_irq_set_enabled(
      &iopmp_, static_cast<dif_iopmp_irq_t>(32), irq_state));
}

TEST_F(IrqSetEnabledTest, Success) {
  dif_toggle_t irq_state;

  // Enable first IRQ.
  irq_state = kDifToggleEnabled;
  EXPECT_MASK32(IOPMP_INTR_ENABLE_REG_OFFSET,
                {{IOPMP_INTR_ENABLE_ACCESS_VIOLATION_BIT, 0x1, true}});
  EXPECT_DIF_OK(dif_iopmp_irq_set_enabled(&iopmp_, kDifIopmpIrqAccessViolation,
                                          irq_state));
}

class IrqDisableAllTest : public IopmpTest {};

TEST_F(IrqDisableAllTest, NullArgs) {
  dif_iopmp_irq_enable_snapshot_t irq_snapshot = 0;

  EXPECT_DIF_BADARG(dif_iopmp_irq_disable_all(nullptr, &irq_snapshot));

  EXPECT_DIF_BADARG(dif_iopmp_irq_disable_all(nullptr, nullptr));
}

TEST_F(IrqDisableAllTest, SuccessNoSnapshot) {
  EXPECT_WRITE32(IOPMP_INTR_ENABLE_REG_OFFSET, 0);
  EXPECT_DIF_OK(dif_iopmp_irq_disable_all(&iopmp_, nullptr));
}

TEST_F(IrqDisableAllTest, SuccessSnapshotAllDisabled) {
  dif_iopmp_irq_enable_snapshot_t irq_snapshot = 0;

  EXPECT_READ32(IOPMP_INTR_ENABLE_REG_OFFSET, 0);
  EXPECT_WRITE32(IOPMP_INTR_ENABLE_REG_OFFSET, 0);
  EXPECT_DIF_OK(dif_iopmp_irq_disable_all(&iopmp_, &irq_snapshot));
  EXPECT_EQ(irq_snapshot, 0);
}

TEST_F(IrqDisableAllTest, SuccessSnapshotAllEnabled) {
  dif_iopmp_irq_enable_snapshot_t irq_snapshot = 0;

  EXPECT_READ32(IOPMP_INTR_ENABLE_REG_OFFSET,
                std::numeric_limits<uint32_t>::max());
  EXPECT_WRITE32(IOPMP_INTR_ENABLE_REG_OFFSET, 0);
  EXPECT_DIF_OK(dif_iopmp_irq_disable_all(&iopmp_, &irq_snapshot));
  EXPECT_EQ(irq_snapshot, std::numeric_limits<uint32_t>::max());
}

class IrqRestoreAllTest : public IopmpTest {};

TEST_F(IrqRestoreAllTest, NullArgs) {
  dif_iopmp_irq_enable_snapshot_t irq_snapshot = 0;

  EXPECT_DIF_BADARG(dif_iopmp_irq_restore_all(nullptr, &irq_snapshot));

  EXPECT_DIF_BADARG(dif_iopmp_irq_restore_all(&iopmp_, nullptr));

  EXPECT_DIF_BADARG(dif_iopmp_irq_restore_all(nullptr, nullptr));
}

TEST_F(IrqRestoreAllTest, SuccessAllEnabled) {
  dif_iopmp_irq_enable_snapshot_t irq_snapshot =
      std::numeric_limits<uint32_t>::max();

  EXPECT_WRITE32(IOPMP_INTR_ENABLE_REG_OFFSET,
                 std::numeric_limits<uint32_t>::max());
  EXPECT_DIF_OK(dif_iopmp_irq_restore_all(&iopmp_, &irq_snapshot));
}

TEST_F(IrqRestoreAllTest, SuccessAllDisabled) {
  dif_iopmp_irq_enable_snapshot_t irq_snapshot = 0;

  EXPECT_WRITE32(IOPMP_INTR_ENABLE_REG_OFFSET, 0);
  EXPECT_DIF_OK(dif_iopmp_irq_restore_all(&iopmp_, &irq_snapshot));
}

}  // namespace
}  // namespace dif_iopmp_autogen_unittest
