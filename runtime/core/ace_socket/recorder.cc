#include "ace_socket/recorder.h"

namespace wenet{

int Recorder::SavePcmFile(const std::string& all_pcm_data)
{    
    printf("Recorder::SavePcmFile()被调用..\n");
    std::ofstream file;
    // file.open("./test.pcm", ios::binary | ios::out | ios::app);
    // for (unsigned int i = 0; i < buf_idx_-2; ++i){
    //     for(unsigned int j = 0; j < MAX_BUF_LEN; ++j)
    //     {
    //         file << pcm_buf_[i][j];
    //     }
    // }
    // // last receive line
    // for (unsigned int j = 0; j < last_rev_; ++j)
    // {
    //     file << pcm_buf_[buf_idx_-1][j];
    // }
    file.open("./test.pcm", std::ios::binary | std::ios::out);
    file << all_pcm_data;

    file.close();
    return 0;

    return 0;
}

} // namespace wenet
