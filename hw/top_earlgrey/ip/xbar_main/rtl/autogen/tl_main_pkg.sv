// Copyright lowRISC contributors (OpenTitan project).
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0
//
// tl_main package generated by `tlgen.py` tool

package tl_main_pkg;

  localparam logic [31:0] ADDR_SPACE_IOPMP__CFG           = 32'h 42000000;
  localparam logic [31:0] ADDR_SPACE_RV_DM__REGS          = 32'h 41200000;
  localparam logic [31:0] ADDR_SPACE_RV_DM__MEM           = 32'h 00010000;
  localparam logic [31:0] ADDR_SPACE_ROM_CTRL__ROM        = 32'h 00008000;
  localparam logic [31:0] ADDR_SPACE_ROM_CTRL__REGS       = 32'h 411e0000;
  localparam logic [1:0][31:0] ADDR_SPACE_PERI                 = {
    32'h 40400000,
    32'h 40000000
  };
  localparam logic [31:0] ADDR_SPACE_SPI_HOST0            = 32'h 40300000;
  localparam logic [31:0] ADDR_SPACE_SPI_HOST1            = 32'h 40310000;
  localparam logic [31:0] ADDR_SPACE_USBDEV               = 32'h 40320000;
  localparam logic [31:0] ADDR_SPACE_FLASH_CTRL__CORE     = 32'h 41000000;
  localparam logic [31:0] ADDR_SPACE_FLASH_CTRL__PRIM     = 32'h 41008000;
  localparam logic [31:0] ADDR_SPACE_FLASH_CTRL__MEM      = 32'h 20000000;
  localparam logic [31:0] ADDR_SPACE_HMAC                 = 32'h 41110000;
  localparam logic [31:0] ADDR_SPACE_KMAC                 = 32'h 41120000;
  localparam logic [31:0] ADDR_SPACE_AES                  = 32'h 41100000;
  localparam logic [31:0] ADDR_SPACE_ENTROPY_SRC          = 32'h 41160000;
  localparam logic [31:0] ADDR_SPACE_CSRNG                = 32'h 41150000;
  localparam logic [31:0] ADDR_SPACE_EDN0                 = 32'h 41170000;
  localparam logic [31:0] ADDR_SPACE_EDN1                 = 32'h 41180000;
  localparam logic [31:0] ADDR_SPACE_RV_PLIC              = 32'h 48000000;
  localparam logic [31:0] ADDR_SPACE_OTBN                 = 32'h 41130000;
  localparam logic [31:0] ADDR_SPACE_KEYMGR               = 32'h 41140000;
  localparam logic [31:0] ADDR_SPACE_RV_CORE_IBEX__CFG    = 32'h 411f0000;
  localparam logic [31:0] ADDR_SPACE_SRAM_CTRL_MAIN__REGS = 32'h 411c0000;
  localparam logic [31:0] ADDR_SPACE_SRAM_CTRL_MAIN__RAM  = 32'h 10000000;

  localparam logic [31:0] ADDR_MASK_IOPMP__CFG           = 32'h 00ffffff;
  localparam logic [31:0] ADDR_MASK_RV_DM__REGS          = 32'h 0000000f;
  localparam logic [31:0] ADDR_MASK_RV_DM__MEM           = 32'h 00000fff;
  localparam logic [31:0] ADDR_MASK_ROM_CTRL__ROM        = 32'h 00007fff;
  localparam logic [31:0] ADDR_MASK_ROM_CTRL__REGS       = 32'h 0000007f;
  localparam logic [1:0][31:0] ADDR_MASK_PERI                 = {
    32'h 003fffff,
    32'h 001fffff
  };
  localparam logic [31:0] ADDR_MASK_SPI_HOST0            = 32'h 0000003f;
  localparam logic [31:0] ADDR_MASK_SPI_HOST1            = 32'h 0000003f;
  localparam logic [31:0] ADDR_MASK_USBDEV               = 32'h 00000fff;
  localparam logic [31:0] ADDR_MASK_FLASH_CTRL__CORE     = 32'h 000001ff;
  localparam logic [31:0] ADDR_MASK_FLASH_CTRL__PRIM     = 32'h 0000007f;
  localparam logic [31:0] ADDR_MASK_FLASH_CTRL__MEM      = 32'h 000fffff;
  localparam logic [31:0] ADDR_MASK_HMAC                 = 32'h 00001fff;
  localparam logic [31:0] ADDR_MASK_KMAC                 = 32'h 00000fff;
  localparam logic [31:0] ADDR_MASK_AES                  = 32'h 000000ff;
  localparam logic [31:0] ADDR_MASK_ENTROPY_SRC          = 32'h 000000ff;
  localparam logic [31:0] ADDR_MASK_CSRNG                = 32'h 0000007f;
  localparam logic [31:0] ADDR_MASK_EDN0                 = 32'h 0000007f;
  localparam logic [31:0] ADDR_MASK_EDN1                 = 32'h 0000007f;
  localparam logic [31:0] ADDR_MASK_RV_PLIC              = 32'h 07ffffff;
  localparam logic [31:0] ADDR_MASK_OTBN                 = 32'h 0000ffff;
  localparam logic [31:0] ADDR_MASK_KEYMGR               = 32'h 000000ff;
  localparam logic [31:0] ADDR_MASK_RV_CORE_IBEX__CFG    = 32'h 000000ff;
  localparam logic [31:0] ADDR_MASK_SRAM_CTRL_MAIN__REGS = 32'h 0000003f;
  localparam logic [31:0] ADDR_MASK_SRAM_CTRL_MAIN__RAM  = 32'h 0001ffff;

  localparam int N_HOST   = 4;
  localparam int N_DEVICE = 25;

  typedef enum int {
    TlIopmpCfg = 0,
    TlRvDmRegs = 1,
    TlRvDmMem = 2,
    TlRomCtrlRom = 3,
    TlRomCtrlRegs = 4,
    TlPeri = 5,
    TlSpiHost0 = 6,
    TlSpiHost1 = 7,
    TlUsbdev = 8,
    TlFlashCtrlCore = 9,
    TlFlashCtrlPrim = 10,
    TlFlashCtrlMem = 11,
    TlHmac = 12,
    TlKmac = 13,
    TlAes = 14,
    TlEntropySrc = 15,
    TlCsrng = 16,
    TlEdn0 = 17,
    TlEdn1 = 18,
    TlRvPlic = 19,
    TlOtbn = 20,
    TlKeymgr = 21,
    TlRvCoreIbexCfg = 22,
    TlSramCtrlMainRegs = 23,
    TlSramCtrlMainRam = 24
  } tl_device_e;

  typedef enum int {
    TlRvCoreIbexCorei = 0,
    TlRvCoreIbexCored = 1,
    TlRvDmSba = 2,
    TlIopmpPrim = 3
  } tl_host_e;

endpackage
