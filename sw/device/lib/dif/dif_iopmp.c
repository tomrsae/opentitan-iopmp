#include "sw/device/lib/dif/dif_iopmp.h"

#include "dif_base.h"
#include "sw/device/lib/base/bitfield.h"
#include "sw/device/lib/base/math.h"
#include "sw/device/lib/base/mmio.h"

void dif_iopmp_md_mask_for_rrid(dif_iopmp_t* iopmp, size_t rrid, uint64_t md_mask, bool lock)
{
    // could return err if locked (MDLCK/MDLCKH/lock bit)

    md_mask <<= 1; // MSB of md_mask is ignored (max 63 MDs)
    md_mask |= lock; // LSB indicates lock

    uint32_t en_reg = md_mask & 0xFFFFFFFFu;
    uint32_t enh_reg = md_mask >> 32u;

    ptrdiff_t rrid_offset = rrid * IOPMP_SRCMD_ENTRY_SIZE;

    mmio_region_write32(iopmp->base, IOPMP_SRCMD_EN_REG_OFFSET + rrid_offset, en_reg);
    mmio_region_write32(iopmp->base, IOPMP_SRCMD_ENH_REG_OFFSET + rrid_offset, enh_reg);
}

void dif_iopmp_add_entry(dif_iopmp_t* iopmp, uint64_t entry_addr, const dif_iopmp_entry_cfg_t* entry_cfg) {
    // could return err if locked (MDCFGLCK)

    uint32_t addr_reg = entry_addr & 0xFFFFFFFFu;
    uint32_t addrh_reg = entry_addr >> 32u;

    uint32_t entry_reg = 0;
    entry_reg = bitfield_bit32_write(entry_reg, IOPMP_ENTRY_CFG_VAL_R_FIELD, entry_cfg->r);
    entry_reg = bitfield_bit32_write(entry_reg, IOPMP_ENTRY_CFG_VAL_W_FIELD, entry_cfg->w);
    entry_reg = bitfield_bit32_write(entry_reg, IOPMP_ENTRY_CFG_VAL_X_FIELD, entry_cfg->x);
    entry_reg = bitfield_field32_write(entry_reg, IOPMP_ENTRY_CFG_VAL_A_FIELD, entry_cfg->a);
    entry_reg = bitfield_bit32_write(entry_reg, IOPMP_ENTRY_CFG_VAL_SIRE_FIELD, entry_cfg->sire);
    entry_reg = bitfield_bit32_write(entry_reg, IOPMP_ENTRY_CFG_VAL_SIWE_FIELD, entry_cfg->siwe);
    entry_reg = bitfield_bit32_write(entry_reg, IOPMP_ENTRY_CFG_VAL_SIXE_FIELD, entry_cfg->sixe);
    entry_reg = bitfield_bit32_write(entry_reg, IOPMP_ENTRY_CFG_VAL_SERE_FIELD, entry_cfg->sere);
    entry_reg = bitfield_bit32_write(entry_reg, IOPMP_ENTRY_CFG_VAL_SEWE_FIELD, entry_cfg->sewe);
    entry_reg = bitfield_bit32_write(entry_reg, IOPMP_ENTRY_CFG_VAL_SEXE_FIELD, entry_cfg->sexe);

    ptrdiff_t entry_offset = entry_addr * IOPMP_ENTRY_ENTRY_SIZE

    // x needs to be ENTRYOFFSET, found in hwcnf - how to best do it? is it constant during runtime?
    mmio_region_write32(iopmp->base, x + entry_offset, addr_reg);
    mmio_region_write32(iopmp->base, x + IOPMP_ENTRY_ADDRH_REL_REG_OFFSET + entry_offset, addrh_reg);
    mmio_region_write32(iopmp->base, x + IOPMP_ENTRY_CFG_REL_REG_OFFSET + entry_offset, entry_reg);
}

void dif_iopmp_mdcfg_set_top_range(dif_iopmp_t* iopmp, size_t md, size_t top_range) {
    // could return err if locked (ENTRYLCK)

    ptrdiff md_offset = md * IOPMP_MDCFG_ENTRY_SIZE;

    uint32_t reg = 0;
    reg = bitfield_field32_write(reg, IOPMP_MDCFG_VAL_T_FIELD, top_range);
    mmio_region_write32(iopmp->base, IOPMP_MDCFG_REG_OFFSET + md_offset, reg);
}