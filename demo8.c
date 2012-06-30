#include <stdio.h>
#include <stdlib.h>
#include <alsa/asoundlib.h>

int main(int argc,char *argv[]){
	int i = 0;
	int err;
	char buf[128];
	snd_pcm_t *playback_handle;
	int rate = 22025;
	int channels = 2;
	snd_pcm_hw_params_t *hw_params;
	if((err = snd_pcm_open(&playback_handle,"default",SND_PCM_STREAM_PLAYBACK,0)) < 0){
		fprintf(stderr,"can't open!%s(%s)\n","default",snd_strerror(err));
		exit(1);
	}
	if((err = snd_pcm_hw_params_malloc(&hw_params) < 0)){
		fprintf(stderr,"can't open!(%s)\n",snd_strerror(err));
		exit(1);
	}
	if((err = snd_pcm_hw_params_any(playback_handle,hw_params)) < 0){
		fprintf(stderr,"can't open(%s)\n",snd_strerror(err));
		exit(1);
	}
	if((err = snd_pcm_hw_params_set_access(playback_handle,hw_params,SND_PCM_ACCESS_RW_INTERLEAVED)) < 0){
		fprintf(stderr,"can't open(%s)\n",snd_strerror(err));
		exit(1);
	}
	if((err = snd_pcm_hw_params_set_format(playback_handle,hw_params,SND_PCM_FORMAT_S16_LE)) < 0){
		fprintf(stderr,"can't set(%s)\n",snd_strerror(err));
		exit(1);
	}
	if((err = snd_pcm_hw_params_set_rate_near(playback_handle,hw_params,&rate,0)) < 0){
		fprintf(stderr,"can't set(%s)\n",snd_strerror(err));
		exit(1);
	}
	if((err = snd_pcm_hw_params_set_channels(playback_handle,hw_params,channels)) < 0){
		fprintf(stderr,"can't set(%s)\n",snd_strerror(err));
		exit(1);
	}
	if((err = snd_pcm_hw_params(playback_handle,hw_params)) < 0){
		fprintf(stderr,"can't open(%s)\n",snd_strerror(err));
		exit(1);
	}
	snd_pcm_hw_params_free(hw_params);
	if((err = snd_pcm_prepare(playback_handle)) < 0){
		fprintf(stderr,"can't prepare(%s)\n",snd_strerror(err));
		exit(1);
	}
	i = 0;
	while(i < 256){
		memset(buf,i,128);
		err = snd_pcm_writei(playback_handle,buf,32);
		//fprintf(stderr,"write %d\n",err);
		if(err < 0){
			snd_pcm_prepare(playback_handle);
			printf("a");
		}
		i++;
	}
	snd_pcm_close(playback_handle);
	exit(0);
}
