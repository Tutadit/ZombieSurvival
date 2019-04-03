#include <osbind.h>
#include "global.h"
#include "raster.h"
#include "input.h"
#include "setup.h"
#include "main.h"

volatile UINT8 * const MFP_PDR_P = MFP_PDR_ADR;
volatile UINT8 * const MFP_AER_P = MFP_AER_ADR;
volatile UINT8 * const MFP_DIR_P = MFP_DIR_ADR;
volatile UINT8 * const MFP_IEA_P = MFP_IEA_ADR;
volatile UINT8 * const MFP_IEB_P = MFP_IEB_ADR;
volatile UINT8 * const MFP_IPA_P = MFP_IPA_ADR;
volatile UINT8 * const MFP_IPB_P = MFP_IPB_ADR;
volatile UINT8 * const MFP_ISA_P = MFP_ISA_ADR;
volatile UINT8 * const MFP_ISB_P = MFP_ISB_ADR;
volatile UINT8 * const MFP_IMA_P = MFP_IMA_ADR;
volatile UINT8 * const MFP_IMB_P = MFP_IMB_ADR;
volatile UINT8 * const MFP_VCR_P = MFP_VCR_ADR;
volatile UINT8 * const MFP_TAC_P = MFP_TAC_ADR;
volatile UINT8 * const MFP_TBC_P = MFP_TBC_ADR;
volatile UINT8 * const MFP_TAD_P = MFP_TAD_ADR;
volatile UINT8 * const MFP_TBD_P = MFP_TBD_ADR;
volatile UINT8 * const MFP_TCD_P = MFP_TCD_ADR;
volatile UINT8 * const MFP_TDD_P = MFP_TDD_ADR;
volatile UINT8 * const MFP_SYC_P = MFP_SYC_ADR;
volatile UINT8 * const MFP_UCR_P = MFP_UCR_ADR;
volatile UINT8 * const MFP_RES_P = MFP_RES_ADR;
volatile UINT8 * const MFP_TRS_P = MFP_TRS_ADR;
volatile UINT8 * const MFP_UAD_P = MFP_UAD_ADR;

void set_up_mfp() {
    long old_ssp = Super(0);
    *MFP_PDR_P = MFP_PDR_DEF;
    *MFP_AER_P = MFP_AER_DEF;
    *MFP_DIR_P = MFP_DIR_DEF;
    *MFP_IEA_P = MFP_IEA_DEF;
    *MFP_IEB_P = MFP_IEB_DEF;
    *MFP_IPA_P = MFP_IPA_DEF;
    *MFP_IPB_P = MFP_IPB_DEF;
    *MFP_ISA_P = MFP_ISA_DEF;
    *MFP_ISB_P = MFP_ISB_DEF;
    *MFP_IMA_P = MFP_IMA_DEF;
    *MFP_IMB_P = MFP_IMB_DEF;
    *MFP_VCR_P = MFP_VCR_DEF;
    *MFP_TAC_P = MFP_TAC_DEF;
    *MFP_TBC_P = MFP_TBC_DEF;
    *MFP_TAD_P = MFP_TAD_DEF;
    *MFP_TBD_P = MFP_TBD_DEF;
    *MFP_TCD_P = MFP_TCD_DEF;
    *MFP_TDD_P = MFP_TDD_DEF;
    *MFP_SYC_P = MFP_SYC_DEF;
    *MFP_UCR_P = MFP_UCR_DEF;
    *MFP_RES_P = MFP_RES_DEF;
    *MFP_TRS_P = MFP_TRS_DEF;
    *MFP_UAD_P = MFP_UAD_DEF;
    Super(old_ssp);
}

void enable_ikbd_irq() {
    long old_ssp = Super(0);
    *IKBD_control = IKBD_CTL_DEF;
    set_ipl(0);
    Super(old_ssp);
}

void install_isrs() {
    install_vector(VECTOR_VBL, vbl_isr);
    install_vector(VECTOR_HBL, hbl_isr);
    install_vector(VECTOR_KBD, kbd_isr);
}

void install_vector(int num, Vector vector) {
    Vector *vectp = (Vector *)((long)num << 2);
    long old_ssp = Super(0);
    *vectp = vector;
    Super(old_ssp);
}
