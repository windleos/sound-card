#include <iostream>
#include <alsa/asoundlib.h>
 
int main()
{
       std::cout << "ALSA library version: " << SND_LIB_VERSION_STR << std::endl;
 
       std::cout << "PCM stream types: " << std::endl;
 
       for (int val=0; val <= SND_PCM_STREAM_LAST; ++val)
              std::cout << snd_pcm_stream_name((snd_pcm_stream_t)val) << std::endl;
       std::cout << std::endl;
 
       std::cout << "PCM access types: " << std::endl;
       for (int val=0; val <= SND_PCM_ACCESS_LAST; ++val)
              std::cout << snd_pcm_access_name((snd_pcm_access_t)val) << std::endl;
       std::cout << std::endl;
 
       std::cout << "PCM subformats: " << std::endl;
       for (int val=0; val <= SND_PCM_SUBFORMAT_LAST; ++val)
              std::cout << snd_pcm_subformat_name((snd_pcm_subformat_t)val) << " (" << snd_pcm_subformat_description((snd_pcm_subformat_t)val) << ")" << std::endl;
       std::cout << std::endl;
 
       std::cout << "PCM states: " << std::endl;
       for (int val=0; val <= SND_PCM_STATE_LAST; ++val)
              std::cout << snd_pcm_state_name((snd_pcm_state_t)val) << std::endl;
       std::cout << std::endl;
 
 
       std::cout << "PCM formats: " << std::endl;
       for (int val=0; val <= SND_PCM_FORMAT_LAST; ++val)
              std::cout << snd_pcm_format_name((snd_pcm_format_t)val) << " (" << snd_pcm_format_description((snd_pcm_format_t)val) << ")" << std::endl;
       std::cout << std::endl;
      
}
