#pragma once
#include <cstdint>
struct CodecProber
{
	enum Codec
	{
		NONE = 0,
		H264 = 1,
		HEVC = 2
	};

	static Codec Probe(const std::uint8_t* data, int size)
	{
		int h264_sps_cnt = 0;
		int h264_pps_cnt = 0;

		//int h264_idr_cnt = 0;	//IDR Ö¡
		//int h264_pf_cnt = 0;	//²Î¿¼


		int hevc_vps_cnt = 0;
		int hevc_sps_cnt = 0;
		int hevc_pps_cnt = 0;
		//int hevc_sei_cnt = 0;
		//int hevc_idr_cnt = 0;

		//int hevc_ss_cnt  = 0; //²Î¿¼

		Codec c = NONE;
		for (int i = 0; data && i < size - 5; i++)
		{
			const std::uint8_t* p = data + i;
			std::uint32_t v = *((std::uint32_t*)p);
			if (v == std::uint32_t(0x01000000) || (v & std::uint32_t(0xFFFFFF)) == 0x010000)
			{
				std::uint8_t h264_nalu_type = (((v == std::uint32_t(0x01000000)) ? p[4] : p[3]) & 0x1F);
				std::uint8_t hecv_nalu_type = (((v == std::uint32_t(0x01000000)) ? p[4] : p[3]) & 0x7E) >> 1;

				if (h264_nalu_type == 7) h264_sps_cnt++;
				if (h264_nalu_type == 8) h264_pps_cnt++;
				/*			if (h264_nalu_type == 5 ) h264_idr_cnt++;
							if (h264_nalu_type == 1 ) h264_pf_cnt++;*/


				if (hecv_nalu_type == 32) hevc_vps_cnt++;
				if (hecv_nalu_type == 33) hevc_sps_cnt++;
				if (hecv_nalu_type == 34) hevc_pps_cnt++;
				//if (hecv_nalu_type == 39) hevc_sei_cnt++;
				//if (hecv_nalu_type == 19) hevc_idr_cnt++;
				//if (hecv_nalu_type == 1)  hevc_ss_cnt++;

			}

			if ((hevc_vps_cnt > 0 && hevc_sps_cnt > 0 && hevc_pps_cnt > 0) /*|| hevc_sei_cnt >0 || hevc_idr_cnt >0 || hevc_ss_cnt>0*/)
			{
				return HEVC;
			}
		}

		if ((h264_sps_cnt > 0 && h264_pps_cnt > 0) /*|| h264_idr_cnt >0 || h264_pf_cnt>0*/)
		{
			return H264;
		}

		return c;
	}
};