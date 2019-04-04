/*
 * Start setup for the 'custom OS' that is this
 * game
 */
#ifndef SETUP_ZS
#define SETUP_ZS
#include "global.h"

#define MFP_PDR_ADR 0xFFFA01
#define MFP_AER_ADR 0xFFFA03
#define MFP_DIR_ADR 0xFFFA05
#define MFP_IEA_ADR 0xFFFA07
#define MFP_IEB_ADR 0xFFFA09
#define MFP_IPA_ADR 0xFFFA0B
#define MFP_IPB_ADR 0xFFFA0D
#define MFP_ISA_ADR 0xFFFA0F
#define MFP_ISB_ADR 0xFFFA11
#define MFP_IMA_ADR 0xFFFA13
#define MFP_IMB_ADR 0xFFFA15
#define MFP_VCR_ADR 0xFFFA17
#define MFP_TAC_ADR 0xFFFA19
#define MFP_TBC_ADR 0xFFFA1B
#define MFP_TAD_ADR 0xFFFA1F
#define MFP_TBD_ADR 0xFFFA21
#define MFP_TCD_ADR 0xFFFA23
#define MFP_TDD_ADR 0xFFFA25
#define MFP_SYC_ADR 0xFFFA27
#define MFP_UCR_ADR 0xFFFA29
#define MFP_RES_ADR 0xFFFA2B
#define MFP_TRS_ADR 0xFFFA2D
#define MFP_UAD_ADR 0xFFFA2F

#define MFP_PDR_DEF 0x73
#define MFP_AER_DEF 0x04
#define MFP_DIR_DEF 0x00
#define MFP_IEA_DEF 0x1E
#define MFP_IEB_DEF 0x64
#define MFP_IPA_DEF 0x00
#define MFP_IPB_DEF 0x00
#define MFP_ISA_DEF 0x00
#define MFP_ISB_DEF 0x00
#define MFP_IMA_DEF 0x1E
#define MFP_IMB_DEF 0x64
#define MFP_VCR_DEF 0x48
#define MFP_TAC_DEF 0x00
#define MFP_TBC_DEF 0x00
#define MFP_TAD_DEF 0x00
#define MFP_TBD_DEF 0x21
#define MFP_TCD_DEF 0x91
#define MFP_TDD_DEF 0x01
#define MFP_SYC_DEF 0x00
#define MFP_UCR_DEF 0x88
#define MFP_RES_DEF 0x01
#define MFP_TRS_DEF 0x81
#define MFP_UAD_DEF 0x00

#define VECTOR_VBL 28
#define VECTOR_HBL 26

#define IKBD_CTL_DEF 0x96

extern volatile UINT8 * const MFP_PDR_P;
extern volatile UINT8 * const MFP_AER_P;
extern volatile UINT8 * const MFP_DIR_P;
extern volatile UINT8 * const MFP_IEA_P;
extern volatile UINT8 * const MFP_IEB_P;
extern volatile UINT8 * const MFP_IPA_P;
extern volatile UINT8 * const MFP_IPB_P;
extern volatile UINT8 * const MFP_ISA_P;
extern volatile UINT8 * const MFP_ISB_P;
extern volatile UINT8 * const MFP_IMA_P;
extern volatile UINT8 * const MFP_IMB_P;
extern volatile UINT8 * const MFP_VCR_P;
extern volatile UINT8 * const MFP_TAC_P;
extern volatile UINT8 * const MFP_TBC_P;
extern volatile UINT8 * const MFP_TAD_P;
extern volatile UINT8 * const MFP_TBD_P;
extern volatile UINT8 * const MFP_TCD_P;
extern volatile UINT8 * const MFP_TDD_P;
extern volatile UINT8 * const MFP_SYC_P;
extern volatile UINT8 * const MFP_UCR_P;
extern volatile UINT8 * const MFP_RES_P;
extern volatile UINT8 * const MFP_TRS_P;
extern volatile UINT8 * const MFP_UAD_P;

typedef void (*Vector)();
/*
 * Instals the following isrs in their respective
 * vecor #:
 *     VBL ISR
 *     HBL ISR
 *     KBD ISR
 */
void install_isrs();
/*
 * Helper methos to install a vector function
 * into their respective vector #
 */
void install_vector(int num, Vector vector);
/*
 * Set up the MFP with the default values
 * needed for runtime.
 */
void set_up_mfp();
/*
 * Enables the interupt request of the
 * IKBD as well as sets the IPL to 0.
 */
void enable_ikbd_irq();


#endif
