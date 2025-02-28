// SPDX-License-Identifier: GPL-2.0-only
/*
 * soc-apci-intel-byt-match.c - tables and support for BYT ACPI enumeration.
 *
 * Copyright (c) 2017, Intel Corporation.
 */

#include <linux/dmi.h>
#include <sound/soc-acpi.h>
#include <sound/soc-acpi-intel-match.h>

static unsigned long byt_machine_id;

#define BYT_THINKPAD_10  1
#define BYT_POV_P1006W   2
#define BYT_AEGEX_10     3

static int byt_thinkpad10_quirk_cb(const struct dmi_system_id *id)
{
	byt_machine_id = BYT_THINKPAD_10;
	return 1;
}

static int byt_pov_p1006w_quirk_cb(const struct dmi_system_id *id)
{
	byt_machine_id = BYT_POV_P1006W;
	return 1;
}

static int byt_aegex10_quirk_cb(const struct dmi_system_id *id)
{
	byt_machine_id = BYT_AEGEX_10;
	return 1;
}

static const struct dmi_system_id byt_table[] = {
	{
		.callback = byt_thinkpad10_quirk_cb,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "ThinkPad 8"),
		},
	},
	{
		.callback = byt_thinkpad10_quirk_cb,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "ThinkPad 10"),
		},
	},
	{
		.callback = byt_thinkpad10_quirk_cb,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "ThinkPad Tablet B"),
		},
	},
	{
		.callback = byt_thinkpad10_quirk_cb,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "Lenovo Miix 2 10"),
		},
	},
	{
		/* Point of View mobii wintab p1006w (v1.0) */
		.callback = byt_pov_p1006w_quirk_cb,
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "Insyde"),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "BayTrail"),
			/* Note 105b is Foxcon's USB/PCI vendor id */
			DMI_EXACT_MATCH(DMI_BOARD_VENDOR, "105B"),
			DMI_EXACT_MATCH(DMI_BOARD_NAME, "0E57"),
		},
	},
	{
		/* Aegex 10 tablet (RU2) */
		.callback = byt_aegex10_quirk_cb,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "AEGEX"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "RU2"),
		},
	},
	{ }
};

/* The Thinkapd 10 and Aegex 10 tablets have the same ID problem */
static struct snd_soc_acpi_mach byt_thinkpad_10 = {
	.id = "10EC5640",
	.drv_name = "cht-bsw-rt5672",
	.fw_filename = "intel/fw_sst_0f28.bin",
	.board = "cht-bsw",
	.sof_fw_filename = "sof-byt.ri",
	.sof_tplg_filename = "sof-byt-rt5670.tplg",
};

static struct snd_soc_acpi_mach byt_pov_p1006w = {
	.id = "10EC5640",
	.drv_name = "bytcr_rt5651",
	.fw_filename = "intel/fw_sst_0f28.bin",
	.board = "bytcr_rt5651",
	.sof_fw_filename = "sof-byt.ri",
	.sof_tplg_filename = "sof-byt-rt5651.tplg",
};

static struct snd_soc_acpi_mach *byt_quirk(void *arg)
{
	struct snd_soc_acpi_mach *mach = arg;

	dmi_check_system(byt_table);

	switch (byt_machine_id) {
	case BYT_THINKPAD_10:
	case BYT_AEGEX_10:
		return &byt_thinkpad_10;
	case BYT_POV_P1006W:
		return &byt_pov_p1006w;
	default:
		return mach;
	}
}

struct snd_soc_acpi_mach snd_soc_acpi_intel_baytrail_legacy_machines[] = {
	{
		.id = "10EC5640",
		.drv_name = "byt-rt5640",
		.fw_filename = "intel/fw_sst_0f28.bin-48kHz_i2s_master",
	},
	{
		.id = "193C9890",
		.drv_name = "byt-max98090",
		.fw_filename = "intel/fw_sst_0f28.bin-48kHz_i2s_master",
	},
	{}
};
EXPORT_SYMBOL_GPL(snd_soc_acpi_intel_baytrail_legacy_machines);

struct snd_soc_acpi_mach  snd_soc_acpi_intel_baytrail_machines[] = {
	{
		.id = "10EC5640",
		.drv_name = "bytcr_rt5640",
		.fw_filename = "intel/fw_sst_0f28.bin",
		.board = "bytcr_rt5640",
		.machine_quirk = byt_quirk,
		.sof_fw_filename = "sof-byt.ri",
		.sof_tplg_filename = "sof-byt-rt5640.tplg",
	},
	{
		.id = "10EC5642",
		.drv_name = "bytcr_rt5640",
		.fw_filename = "intel/fw_sst_0f28.bin",
		.board = "bytcr_rt5640",
		.sof_fw_filename = "sof-byt.ri",
		.sof_tplg_filename = "sof-byt-rt5640.tplg",
	},
	{
		.id = "INTCCFFD",
		.drv_name = "bytcr_rt5640",
		.fw_filename = "intel/fw_sst_0f28.bin",
		.board = "bytcr_rt5640",
		.sof_fw_filename = "sof-byt.ri",
		.sof_tplg_filename = "sof-byt-rt5640.tplg",
	},
	{
		.id = "10EC5651",
		.drv_name = "bytcr_rt5651",
		.fw_filename = "intel/fw_sst_0f28.bin",
		.board = "bytcr_rt5651",
		.sof_fw_filename = "sof-byt.ri",
		.sof_tplg_filename = "sof-byt-rt5651.tplg",
	},
	{
		.id = "10EC3277",
		.drv_name = "bytcr_rt5660",
		.fw_filename = "intel/fw_sst_0f28.bin",
		.board = "bytcr_rt5660",
		.sof_fw_filename = "intel/reef-byt.ri",
		.sof_tplg_filename = "intel/reef-byt-rt5660.tplg",
	},
	{
		.id = "DLGS7212",
		.drv_name = "bytcht_da7213",
		.fw_filename = "intel/fw_sst_0f28.bin",
		.board = "bytcht_da7213",
		.sof_fw_filename = "sof-byt.ri",
		.sof_tplg_filename = "sof-byt-da7213.tplg",
	},
	{
		.id = "DLGS7213",
		.drv_name = "bytcht_da7213",
		.fw_filename = "intel/fw_sst_0f28.bin",
		.board = "bytcht_da7213",
		.sof_fw_filename = "sof-byt.ri",
		.sof_tplg_filename = "sof-byt-da7213.tplg",
	},
	{
		.id = "ESSX8316",
		.drv_name = "bytcht_es8316",
		.fw_filename = "intel/fw_sst_0f28.bin",
		.board = "bytcht_es8316",
		.sof_fw_filename = "sof-byt.ri",
		.sof_tplg_filename = "sof-byt-es8316.tplg",
	},
	{
		.id = "10EC5682",
		.drv_name = "sof_rt5682",
		.sof_fw_filename = "sof-byt.ri",
		.sof_tplg_filename = "sof-byt-rt5682.tplg",
	},
	/* some Baytrail platforms rely on RT5645, use CHT machine driver */
	{
		.id = "10EC5645",
		.drv_name = "cht-bsw-rt5645",
		.fw_filename = "intel/fw_sst_0f28.bin",
		.board = "cht-bsw",
		.sof_fw_filename = "sof-byt.ri",
		.sof_tplg_filename = "sof-byt-rt5645.tplg",
	},
	{
		.id = "10EC5648",
		.drv_name = "cht-bsw-rt5645",
		.fw_filename = "intel/fw_sst_0f28.bin",
		.board = "cht-bsw",
		.sof_fw_filename = "sof-byt.ri",
		.sof_tplg_filename = "sof-byt-rt5645.tplg",
	},
	/* use CHT driver to Baytrail Chromebooks */
	{
		.id = "193C9890",
		.drv_name = "cht-bsw-max98090",
		.fw_filename = "intel/fw_sst_0f28.bin",
		.board = "cht-bsw",
		.sof_fw_filename = "sof-byt.ri",
		.sof_tplg_filename = "sof-byt-max98090.tplg",
	},
#if IS_ENABLED(CONFIG_SND_SOC_INTEL_BYT_CHT_NOCODEC_MACH)
	/*
	 * This is always last in the table so that it is selected only when
	 * enabled explicitly and there is no codec-related information in SSDT
	 */
	{
		.id = "80860F28",
		.drv_name = "bytcht_nocodec",
		.fw_filename = "intel/fw_sst_0f28.bin",
		.board = "bytcht_nocodec",
	},
#endif
	{},
};
EXPORT_SYMBOL_GPL(snd_soc_acpi_intel_baytrail_machines);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Intel Common ACPI Match module");
