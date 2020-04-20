#include <LIBSPU.H>

class AudioService {
public:
    static void initialize();

    static void audioTransferVagToSPU(unsigned char *sound, unsigned long sound_size, unsigned long int voice_channel);

//    * @return sum of `values`, or 0.0 if `values` is empty.
/**
 * Plays audio from provided voice channel buffer.
 *
 * @param voice_channel Voice channel that will play the sound.
 */
    static void audioPlay(unsigned long voice_channel);

    static SpuCommonAttr l_c_attr;
    static unsigned long l_vag1_spu_addr;
    static SpuVoiceAttr g_s_attr;
};
