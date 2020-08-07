#include "AudioService.h"
#include <LIBSPU.H>

#define SOUND_MALLOC_MAX 10
#define VAG_METADATA_SIZE 0x30

SpuCommonAttr AudioService::l_c_attr;
unsigned long AudioService::l_vag1_spu_addr;
SpuVoiceAttr  AudioService::g_s_attr;

void AudioService::initialize() {
	SpuInit();
	SpuInitMalloc(SOUND_MALLOC_MAX, (char *) (SPU_MALLOC_RECSIZ * (SOUND_MALLOC_MAX + 1)));
	AudioService::l_c_attr.mask = (SPU_COMMON_MVOLL | SPU_COMMON_MVOLR);
	AudioService::l_c_attr.mvol.left = 0x3fff; // set master left volume
	AudioService::l_c_attr.mvol.right = 0x3fff; // set master right volume
	SpuSetCommonAttr(&AudioService::l_c_attr);
}

void AudioService::audioTransferVagToSPU(unsigned char * sound, unsigned long sound_size, unsigned long int voice_channel, short volume) {
	SpuSetTransferMode(SpuTransByDMA); // set transfer mode to DMA
	l_vag1_spu_addr = SpuMalloc((long) sound_size); // allocate SPU memory for sound 1
	SpuSetTransferStartAddr(l_vag1_spu_addr); // set transfer starting address to malloced area
	SpuWrite(sound + VAG_METADATA_SIZE, sound_size - VAG_METADATA_SIZE); // perform actual transfer
	SpuIsTransferCompleted(SPU_TRANSFER_WAIT); // wait for DMA to complete
	// mask which specific voice attributes are to be set
	g_s_attr.mask =
			(
					SPU_VOICE_VOLL |
					SPU_VOICE_VOLR |
					SPU_VOICE_PITCH |
					SPU_VOICE_WDSA |
					SPU_VOICE_ADSR_AMODE |
					SPU_VOICE_ADSR_SMODE |
					SPU_VOICE_ADSR_RMODE |
					SPU_VOICE_ADSR_AR |
					SPU_VOICE_ADSR_DR |
					SPU_VOICE_ADSR_SR |
					SPU_VOICE_ADSR_RR |
					SPU_VOICE_ADSR_SL
			);

	g_s_attr.voice = (voice_channel);

	g_s_attr.volume.left = (short) 0x1fff & volume;
	g_s_attr.volume.right = (short) 0x1fff & volume;

	g_s_attr.pitch = 0x1000;
	g_s_attr.addr = l_vag1_spu_addr;
	g_s_attr.a_mode = SPU_VOICE_LINEARIncN;
	g_s_attr.s_mode = SPU_VOICE_LINEARIncN;
	g_s_attr.r_mode = SPU_VOICE_LINEARDecN;
	g_s_attr.ar = 0x0;
	g_s_attr.dr = 0x0;
	g_s_attr.sr = 0x0;
	g_s_attr.rr = 0x0;
	g_s_attr.sl = 0xf;

	SpuSetVoiceAttr(&g_s_attr);
}

void AudioService::audioPlay(unsigned long int voice_channel) {
	SpuSetKey(SpuOn, voice_channel);
}

void AudioService::setVolume(unsigned long int voice_channel, short volume) {
	SpuSetVoiceVolume(voice_channel, volume, volume);
}
