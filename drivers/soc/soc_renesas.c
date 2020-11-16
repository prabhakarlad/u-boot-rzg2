// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2014-2016 Glider bvba
 * Copyright (C) 2020 Renesas Electronics Corp.
 *
 */

#include <common.h>
#include <dm.h>
#include <dm/device-internal.h>
#include <soc.h>

#include <asm/io.h>

struct soc_renesas_priv {
	const char *family;
	const char *soc_id;
	char revision[6];
};

struct renesas_family {
	const char name[16];
	u32 reg;			/* CCCR or PRR, if not in DT */
};

static const struct renesas_family fam_rcar_gen3 __maybe_unused = {
	.name	= "R-Car Gen3",
	.reg	= 0xfff00044,		/* PRR (Product Register) */
};

static const struct renesas_family fam_rzg2 __maybe_unused = {
	.name	= "RZ/G2",
	.reg	= 0xfff00044,		/* PRR (Product Register) */
};

struct renesas_soc {
	const struct renesas_family *family;
	u8 id;
};

#ifdef CONFIG_R8A774A1
static const struct renesas_soc soc_rz_g2m = {
	.family	= &fam_rzg2,
	.id	= 0x52,
};
#endif

#ifdef CONFIG_R8A774B1
static const struct renesas_soc soc_rz_g2n = {
	.family = &fam_rzg2,
	.id     = 0x55,
};
#endif

#ifdef CONFIG_R8A774C0
static const struct renesas_soc soc_rz_g2e = {
	.family	= &fam_rzg2,
	.id	= 0x57,
};
#endif

#ifdef CONFIG_R8A774E1
static const struct renesas_soc soc_rz_g2h = {
	.family	= &fam_rzg2,
	.id	= 0x4f,
};
#endif

#ifdef CONFIG_R8A7795
static const struct renesas_soc soc_rcar_h3 = {
	.family	= &fam_rcar_gen3,
	.id	= 0x4f,
};
#endif

#ifdef CONFIG_R8A7796
static const struct renesas_soc soc_rcar_m3_w = {
	.family	= &fam_rcar_gen3,
	.id	= 0x52,
};
#endif

#ifdef CONFIG_R8A77965
static const struct renesas_soc soc_rcar_m3_n = {
	.family = &fam_rcar_gen3,
	.id     = 0x55,
};
#endif

#ifdef CONFIG_R8A77970
static const struct renesas_soc soc_rcar_v3m = {
	.family	= &fam_rcar_gen3,
	.id	= 0x54,
};
#endif

#ifdef CONFIG_R8A77980
static const struct renesas_soc soc_rcar_v3h = {
	.family	= &fam_rcar_gen3,
	.id	= 0x56,
};
#endif

#ifdef CONFIG_R8A77990
static const struct renesas_soc soc_rcar_e3 = {
	.family	= &fam_rcar_gen3,
	.id	= 0x57,
};
#endif

#ifdef CONFIG_R8A77995
static const struct renesas_soc soc_rcar_d3 = {
	.family	= &fam_rcar_gen3,
	.id	= 0x58,
};
#endif

static int soc_renesas_get_family(struct udevice *dev, char *buf, int size)
{
	struct soc_renesas_priv *priv = dev_get_priv(dev);

	snprintf(buf, size, "%s", priv->family);

	return 0;
}

static int soc_renesas_get_revision(struct udevice *dev, char *buf, int size)
{
	struct soc_renesas_priv *priv = dev_get_priv(dev);

	snprintf(buf, size, "%s", priv->revision);

	return 0;
}

static int soc_renesas_get_soc_id(struct udevice *dev, char *buf, int size)
{
	struct soc_renesas_priv *priv = dev_get_priv(dev);

	snprintf(buf, size, "%s", priv->soc_id);

	return 0;
}

static const struct udevice_id renesas_socs[] = {
#ifdef CONFIG_R8A774A1
	{ .compatible = "renesas,r8a774a1",	.data = (ulong)&soc_rz_g2m, },
#endif
#ifdef CONFIG_R8A774B1
	{ .compatible = "renesas,r8a774b1",	.data = (ulong)&soc_rz_g2n, },
#endif
#ifdef CONFIG_R8A774C0
	{ .compatible = "renesas,r8a774c0",	.data = (ulong)&soc_rz_g2e, },
#endif
#ifdef CONFIG_R8A774E1
	{ .compatible = "renesas,r8a774e1",	.data = (ulong)&soc_rz_g2h, },
#endif
#ifdef CONFIG_R8A7795
	{ .compatible = "renesas,r8a7795",	.data = (ulong)&soc_rcar_h3, },
#endif
#ifdef CONFIG_R8A7796
	{ .compatible = "renesas,r8a7796",	.data = (ulong)&soc_rcar_m3_w, },
#endif
#ifdef CONFIG_R8A77965
	{ .compatible = "renesas,r8a77965",	.data = (ulong)&soc_rcar_m3_n, },
#endif
#ifdef CONFIG_R8A77970
	{ .compatible = "renesas,r8a77970",	.data = (ulong)&soc_rcar_v3m, },
#endif
#ifdef CONFIG_R8A77980
	{ .compatible = "renesas,r8a77980",	.data = (ulong)&soc_rcar_v3h, },
#endif
#ifdef CONFIG_R8A77990
	{ .compatible = "renesas,r8a77990",	.data = (ulong)&soc_rcar_e3, },
#endif
#ifdef CONFIG_R8A77995
	{ .compatible = "renesas,r8a77995",	.data = (ulong)&soc_rcar_d3, },
#endif
	{ /* sentinel */ }
};

static const struct udevice_id prr_ids[] = {
	{ .compatible = "renesas,prr" },
	{ /* sentinel */ }
};

static const struct soc_ops soc_renesas_ops = {
	.get_family = soc_renesas_get_family,
	.get_revision = soc_renesas_get_revision,
	.get_soc_id = soc_renesas_get_soc_id,
};

int soc_renesas_probe(struct udevice *dev)
{
	struct soc_renesas_priv *priv = dev_get_priv(dev);
	void *prr_addr = dev_read_addr_ptr(dev);
	unsigned int product, eshi = 0, eslo;
	const struct renesas_family *family;
	const struct udevice_id *match;
	struct renesas_soc *soc;
	ofnode root_node;

	if (!prr_addr)
		return -EINVAL;

	root_node = ofnode_path("/");
	match = of_match_node(renesas_socs, root_node);
	if (!match) {
		printf("SoC entry is missing in DT\n");
		return -EINVAL;
	}

	soc = (struct renesas_soc *)match->data;
	family = soc->family;

	product = readl(prr_addr);
	/* R-Car M3-W ES1.1 incorrectly identifies as ES2.0 */
	if ((product & 0x7fff) == 0x5210)
		product ^= 0x11;
	/* R-Car M3-W ES1.3 incorrectly identifies as ES2.1 */
	if ((product & 0x7fff) == 0x5211)
		product ^= 0x12;
	if (soc->id && ((product >> 8) & 0xff) != soc->id) {
		printf("SoC mismatch (product = 0x%x)\n", product);
		return -EINVAL;
	}
	eshi = ((product >> 4) & 0x0f) + 1;
	eslo = product & 0xf;

	priv->family = family->name;
	priv->soc_id = strchr(match->compatible, ',') + 1;
	snprintf(priv->revision, sizeof(priv->revision), "ES%u.%u", eshi, eslo);

	return 0;
}

U_BOOT_DRIVER(soc_renesas) = {
	.name           = "soc_renesas",
	.id             = UCLASS_SOC,
	.ops		= &soc_renesas_ops,
	.of_match       = prr_ids,
	.probe          = soc_renesas_probe,
	.priv_auto_alloc_size  = sizeof(struct soc_renesas_priv),
};
