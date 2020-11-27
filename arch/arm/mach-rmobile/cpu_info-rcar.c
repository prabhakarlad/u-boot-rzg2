// SPDX-License-Identifier: GPL-2.0
/*
 * arch/arm/cpu/armv7/rmobile/cpu_info-rcar.c
 *
 * Copyright (C) 2013,2014 Renesas Electronics Corporation
 */
#include <common.h>
#include <asm/io.h>
#include <soc.h>

#define PRR_MASK		0x7fff
#define R8A7796_REV_1_0		0x5200
#define R8A7796_REV_1_1		0x5210
#define R8A7796_REV_1_3		0x5211

static u32 rmobile_get_prr(void)
{
#ifdef CONFIG_RCAR_GEN3
	return readl(0xFFF00044);
#else
	return readl(0xFF000044);
#endif
}

static bool is_rzg_family(void)
{
	bool rzg_family_type = false;
	struct udevice *soc;
	char name[16];

	if (!(soc_get(&soc) || soc_get_family(soc, name, 16))) {
		if (!strcmp(name, "RZ/G2"))
			rzg_family_type = true;
	}

	return rzg_family_type;
}

u32 rmobile_get_cpu_type(void)
{
	u32 soc_id = (rmobile_get_prr() & 0x7F00) >> 8;

	if (is_rzg_family())
		soc_id |= RZG_CPU_MASK;

	return soc_id;
}

u32 rmobile_get_cpu_rev_integer(void)
{
	const u32 prr = rmobile_get_prr();
	const u32 rev = prr & PRR_MASK;

	if (rev == R8A7796_REV_1_1 || rev == R8A7796_REV_1_3)
		return 1;
	else
		return ((prr & 0x000000F0) >> 4) + 1;
}

u32 rmobile_get_cpu_rev_fraction(void)
{
	const u32 prr = rmobile_get_prr();
	const u32 rev = prr & PRR_MASK;

	if (rev == R8A7796_REV_1_1)
		return 1;
	else if (rev == R8A7796_REV_1_3)
		return 3;
	else
		return prr & 0x0000000F;
}
