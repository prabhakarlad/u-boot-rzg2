#ifndef __ASM_ARCH_RMOBILE_H
#define __ASM_ARCH_RMOBILE_H

#if defined(CONFIG_ARCH_RMOBILE)
#if defined(CONFIG_SH73A0)
#include <asm/arch/sh73a0.h>
#elif defined(CONFIG_R8A7740)
#include <asm/arch/r8a7740.h>
#elif defined(CONFIG_R8A7790)
#include <asm/arch/r8a7790.h>
#elif defined(CONFIG_R8A7791)
#include <asm/arch/r8a7791.h>
#elif defined(CONFIG_R8A7792)
#include <asm/arch/r8a7792.h>
#elif defined(CONFIG_R8A7793)
#include <asm/arch/r8a7793.h>
#elif defined(CONFIG_R8A7794)
#include <asm/arch/r8a7794.h>
#elif defined(CONFIG_RCAR_GEN3)
#include <asm/arch/rcar-gen3-base.h>
#elif defined(CONFIG_R7S72100)
#else
#error "SOC Name not defined"
#endif
#endif /* CONFIG_ARCH_RMOBILE */

/* PRR IDs */
#define SOC_ID_SH73A0		0x37
#define SOC_ID_R8A7740		0x40
#define SOC_ID_R8A774A1		0x52
#define SOC_ID_R8A774B1		0x55
#define SOC_ID_R8A774C0		0x57
#define SOC_ID_R8A774E1		0x4F
#define SOC_ID_R8A7790		0x45
#define SOC_ID_R8A7791		0x47
#define SOC_ID_R8A7792		0x4A
#define SOC_ID_R8A7793		0x4B
#define SOC_ID_R8A7794		0x4C
#define SOC_ID_R8A7795		0x4F
#define SOC_ID_R8A7796		0x52
#define SOC_ID_R8A77965		0x55
#define SOC_ID_R8A77970		0x54
#define SOC_ID_R8A77980		0x56
#define SOC_ID_R8A77990		0x57
#define SOC_ID_R8A77995		0x58

/* CPU IDs */
#define RMOBILE_CPU_TYPE_SH73A0		SOC_ID_SH73A0
#define RMOBILE_CPU_TYPE_R8A7740	SOC_ID_R8A7740
#define RMOBILE_CPU_TYPE_R8A774A1	(SOC_ID_R8A774A1 | RZG_CPU_MASK)
#define RMOBILE_CPU_TYPE_R8A774B1	(SOC_ID_R8A774B1 | RZG_CPU_MASK)
#define RMOBILE_CPU_TYPE_R8A774C0	(SOC_ID_R8A774C0 | RZG_CPU_MASK)
#define RMOBILE_CPU_TYPE_R8A774E1	(SOC_ID_R8A774E1 | RZG_CPU_MASK)
#define RMOBILE_CPU_TYPE_R8A7790	SOC_ID_R8A7790
#define RMOBILE_CPU_TYPE_R8A7791	SOC_ID_R8A7791
#define RMOBILE_CPU_TYPE_R8A7792	SOC_ID_R8A7792
#define RMOBILE_CPU_TYPE_R8A7793	SOC_ID_R8A7793
#define RMOBILE_CPU_TYPE_R8A7794	SOC_ID_R8A7794
#define RMOBILE_CPU_TYPE_R8A7795	SOC_ID_R8A7795
#define RMOBILE_CPU_TYPE_R8A7796	SOC_ID_R8A7796
#define RMOBILE_CPU_TYPE_R8A77965	SOC_ID_R8A77965
#define RMOBILE_CPU_TYPE_R8A77970	SOC_ID_R8A77970
#define RMOBILE_CPU_TYPE_R8A77980	SOC_ID_R8A77980
#define RMOBILE_CPU_TYPE_R8A77990	SOC_ID_R8A77990
#define RMOBILE_CPU_TYPE_R8A77995	SOC_ID_R8A77995

/*
 * R-Car and RZ/G SoC's share same PRR ID's for the same SoC type. The
 * RZG_CPU_MASK is used to provide a unique CPU identification for RZ/G SoC's.
 */
#define RZG_CPU_MASK 0x1000

#ifndef __ASSEMBLY__
u32 rmobile_get_cpu_type(void);
u32 rmobile_get_cpu_rev_integer(void);
u32 rmobile_get_cpu_rev_fraction(void);
#endif /* __ASSEMBLY__ */

#endif /* __ASM_ARCH_RMOBILE_H */
