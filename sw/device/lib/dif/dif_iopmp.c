#include "sw/device/lib/dif/dif_iopmp.h"

#include "dif_base.h"
#include "sw/device/lib/base/bitfield.h"
#include "sw/device/lib/base/math.h"
#include "sw/device/lib/base/mmio.h"

void dif_iopmp_get_config(dif_iopmp_t* iopmp, dif_iopmp_config_t* config)
{
    uint32_t entryoffset_reg = mmio_region_read32(iopmp->base_addr, IOPMP_ENTRYOFFSET_REG_OFFSET);

    config->entryoffset = (int32_t)entryoffset_reg;
}

void dif_iopmp_set_md_mask_for_rrid(dif_iopmp_t* iopmp, uint32_t rrid, uint32_t md_mask, bool lock)
{
    md_mask <<= 1; // MSB of md_mask is ignored
    md_mask |= lock; // LSB indicates lock

    uint32_t en_reg = md_mask;

    ptrdiff_t rrid_offset = ((int)rrid) * IOPMP_SRCMD_ENTRY_SIZE;
    
    mmio_region_write32(iopmp->base_addr, IOPMP_SRCMD_EN_REG_OFFSET + rrid_offset, en_reg);
}

void dif_iopmp_get_md_mask_for_rrid(dif_iopmp_t* iopmp, uint32_t rrid, uint32_t* md_mask, bool* is_locked)
{
    ptrdiff_t rrid_offset = ((int)rrid) * IOPMP_SRCMD_ENTRY_SIZE;

    uint32_t en_reg = mmio_region_read32(iopmp->base_addr, IOPMP_SRCMD_EN_REG_OFFSET + rrid_offset);

    *is_locked = en_reg & 0x1; // LSB indicates lock
    *md_mask = (en_reg >> 1);
}


void dif_iopmp_add_entry(dif_iopmp_t* iopmp, const dif_iopmp_config_t* iopmp_cfg, uint32_t entry_addr, const dif_iopmp_entry_cfg_t* entry_cfg) {
    static int num_entries = 0;

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

    ptrdiff_t entry_offset = num_entries++ * IOPMP_ENTRY_ENTRY_SIZE;

    mmio_region_write32(iopmp->base_addr, iopmp_cfg->entryoffset + entry_offset, entry_addr);
    mmio_region_write32(iopmp->base_addr, iopmp_cfg->entryoffset + IOPMP_ENTRY_CFG_REL_REG_OFFSET + entry_offset, entry_reg);
}

void dif_iopmp_get_entry(dif_iopmp_t* iopmp, const dif_iopmp_config_t* iopmp_cfg, int entry, uint32_t* entry_addr, dif_iopmp_entry_cfg_t* entry_cfg) {
    ptrdiff_t entry_offset = entry * IOPMP_ENTRY_ENTRY_SIZE;

    *entry_addr = mmio_region_read32(iopmp->base_addr, iopmp_cfg->entryoffset + entry_offset);
    uint32_t entry_reg = mmio_region_read32(iopmp->base_addr, iopmp_cfg->entryoffset + IOPMP_ENTRY_CFG_REL_REG_OFFSET + entry_offset);

    entry_cfg->r = bitfield_bit32_read(entry_reg, IOPMP_ENTRY_CFG_VAL_R_FIELD);
    entry_cfg->w = bitfield_bit32_read(entry_reg, IOPMP_ENTRY_CFG_VAL_W_FIELD);
    entry_cfg->x = bitfield_bit32_read(entry_reg, IOPMP_ENTRY_CFG_VAL_X_FIELD);
    entry_cfg->a = bitfield_field32_read(entry_reg, IOPMP_ENTRY_CFG_VAL_A_FIELD);
    entry_cfg->sire = bitfield_bit32_read(entry_reg, IOPMP_ENTRY_CFG_VAL_SIRE_FIELD);
    entry_cfg->siwe = bitfield_bit32_read(entry_reg, IOPMP_ENTRY_CFG_VAL_SIWE_FIELD);
    entry_cfg->sixe = bitfield_bit32_read(entry_reg, IOPMP_ENTRY_CFG_VAL_SIXE_FIELD);
    entry_cfg->sere = bitfield_bit32_read(entry_reg, IOPMP_ENTRY_CFG_VAL_SERE_FIELD);
    entry_cfg->sewe = bitfield_bit32_read(entry_reg, IOPMP_ENTRY_CFG_VAL_SEWE_FIELD);
    entry_cfg->sexe = bitfield_bit32_read(entry_reg, IOPMP_ENTRY_CFG_VAL_SEXE_FIELD);
}

void dif_iopmp_mdcfg_set_top_range(dif_iopmp_t* iopmp, uint32_t md, uint32_t top_range) {
    ptrdiff_t md_offset = ((int)md) * IOPMP_MDCFG_ENTRY_SIZE;

    uint32_t reg = 0;
    reg = bitfield_field32_write(reg, IOPMP_MDCFG_VAL_T_FIELD, top_range);
    mmio_region_write32(iopmp->base_addr, IOPMP_MDCFG_REG_OFFSET + md_offset, reg);
}

void dif_iopmp_mdcfg_get_top_range(dif_iopmp_t* iopmp, uint32_t md, uint32_t* top_range) {
    ptrdiff_t md_offset = ((int)md) * IOPMP_MDCFG_ENTRY_SIZE;

    uint32_t reg = mmio_region_read32(iopmp->base_addr, IOPMP_MDCFG_REG_OFFSET + md_offset);
    *top_range = bitfield_field32_read(reg, IOPMP_MDCFG_VAL_T_FIELD);
}

bool dif_iopmp_cmp_entry_cfg(const dif_iopmp_entry_cfg_t* self, const dif_iopmp_entry_cfg_t* other)
{
    return
        self->r == other->r &&
        self->w == other->w &&
        self->x == other->x &&
        self->a == other->a &&
        self->sire == other->sire &&
        self->siwe == other->siwe &&
        self->sixe == other->sixe &&
        self->sere == other->sere &&
        self->sewe == other->sewe &&
        self->sexe == other->sexe;
}