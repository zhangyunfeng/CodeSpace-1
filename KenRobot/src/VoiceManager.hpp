#ifndef VOICEMANAGER_H
#define VOICEMANAGER_H

#include <string>

#include "../Linux_voice/include/qtts.h"
#include "../Linux_voice/include/msp_cmn.h"
#include "../Linux_voice/include/msp_errors.h"

class VoiceManager {
  public:
    static VoiceManager& GetInstance();

    int ConvertText2Speech(const std::string&& text, const std::string&& dest_path);
  private:
    void init();
    void loginXF();
    VoiceManager();
    
};

    
#endif /* VOICEMANAGER_H */
