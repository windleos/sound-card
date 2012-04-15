#include <iostream>
#include <alsa/asoundlib.h>
 
int main()
{
	int rc;
	snd_pcm_t* handle;
	snd_pcm_hw_params_t* params;
	unsigned int val;
	unsigned int val2;
	int dir;
	snd_pcm_uframes_t frames;

	if ( (rc = snd_pcm_open(&handle, "default", SND_PCM_STREAM_PLAYBACK, 0)) < 0)
	{
		std::cerr << "unable to open pcm devices: " << snd_strerror(rc) << std::endl;
		exit(1);
	}

	snd_pcm_hw_params_alloca(&params);

	snd_pcm_hw_params_any(handle, params);

	snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_RW_INTERLEAVED);

	snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_S16_LE);

	snd_pcm_hw_params_set_channels(handle, params, 2);

	val = 44100;

	snd_pcm_hw_params_set_rate_near(handle, params, &val, &dir);

	if ( (rc = snd_pcm_hw_params(handle, params)) < 0)
	{
		std::cerr << "unable to set hw parameters: " << snd_strerror(rc) << std::endl;
		exit(1);
	}

	std::cout << "PCM handle name = " << snd_pcm_name(handle) << std::endl;

	std::cout << "PCM state = " << snd_pcm_state_name(snd_pcm_state(handle)) << std::endl;

	snd_pcm_hw_params_get_access(params, (snd_pcm_access_t *)&val);

	std::cout << "access type = " << snd_pcm_access_name((snd_pcm_access_t)val) << std::endl;

	snd_pcm_hw_params_get_format(params, (snd_pcm_format_t*)(&val));

	std::cout << "format = '" << snd_pcm_format_name((snd_pcm_format_t)val) << "' (" << snd_pcm_format_description((snd_pcm_format_t)val) << ")" << std::endl;

	snd_pcm_hw_params_get_subformat(params, (snd_pcm_subformat_t *)&val);
	std::cout << "subformat = '" <<
		snd_pcm_subformat_name((snd_pcm_subformat_t)val) << "' (" << snd_pcm_subformat_description((snd_pcm_subformat_t)val) << ")" << std::endl;

	snd_pcm_hw_params_get_channels(params, &val);
	std::cout << "channels = " << val << std::endl;

	snd_pcm_hw_params_get_rate(params, &val, &dir);
	std::cout << "rate = " << val << " bps" << std::endl;

	snd_pcm_hw_params_get_period_time(params, &val, &dir);
	std::cout << "period time = " << val << " us" << std::endl;

	snd_pcm_hw_params_get_period_size(params, &frames, &dir);
	std::cout << "period size = " << static_cast<int>(frames) << " frames" << std::endl;

	snd_pcm_hw_params_get_buffer_time(params, &val, &dir);
	std::cout << "buffer time = " << val << " us" << std::endl;

	snd_pcm_hw_params_get_buffer_size(params, (snd_pcm_uframes_t *) &val);
	std::cout << "buffer size = " << val << " frames" << std::endl;

	snd_pcm_hw_params_get_periods(params, &val, &dir);
	std::cout << "periods per buffer = " << val << " frames" << std::endl;

	snd_pcm_hw_params_get_rate_numden(params, &val, &val2);
	std::cout << "exact rate = " << val/val2 << " bps" << std::endl;

	val = snd_pcm_hw_params_get_sbits(params);
	std::cout << "significant bits = " << val << std::endl;

	snd_pcm_hw_params_get_tick_time(params, &val, &dir);
	std::cout << "tick time = " << val << " us" << std::endl;

	val = snd_pcm_hw_params_is_batch(params);
	std::cout << "is batch = " << val << std::endl;

	val = snd_pcm_hw_params_is_block_transfer(params);
	std::cout << "is block transfer = " << val << std::endl;

	val = snd_pcm_hw_params_is_double(params);
	std::cout << "is double = " << val << std::endl;

	val = snd_pcm_hw_params_is_half_duplex(params);
	std::cout << "is half duplex = " << val << std::endl;

	val = snd_pcm_hw_params_is_joint_duplex(params);
	std::cout << "is joint duplex = " << val << std::endl;

	val = snd_pcm_hw_params_can_overrange(params);
	std::cout << "can overrange = " << val << std::endl;

	val = snd_pcm_hw_params_can_mmap_sample_resolution(params);
	std::cout << "can mmap = " << val << std::endl;

	val = snd_pcm_hw_params_can_pause(params);
	std::cout << "can pause = " << val << std::endl;

	val = snd_pcm_hw_params_can_resume(params);
	std::cout << "can resume = " << val << std::endl;

	val = snd_pcm_hw_params_can_sync_start(params);
	std::cout << "can sync start = " << val << std::endl;

	snd_pcm_close(handle);

	return 0;
}
