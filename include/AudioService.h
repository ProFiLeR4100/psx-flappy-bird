#include <LIBSPU.H>

#ifndef AUDIO_SERVICE_H
#define AUDIO_SERVICE_H

struct AudioService {
	static void initialize();

	static void audioTransferVagToSPU(unsigned char *sound, unsigned long sound_size, unsigned long int voice_channel, short volume);

//	* @return sum of `values`, or 0.0 if `values` is empty.
/**
 * Plays audio from provided voice channel buffer.
 *
 * @param voice_channel Voice channel that will play the sound.
 */
	static void audioPlay(unsigned long voice_channel);

	static SpuCommonAttr l_c_attr;
	static unsigned long l_vag1_spu_addr;
	static SpuVoiceAttr g_s_attr;

	static void setVolume(unsigned long voice_channel, short volume);
};

#endif // AUDIO_SERVICE_H