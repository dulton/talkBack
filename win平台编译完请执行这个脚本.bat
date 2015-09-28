path
copy bin\debug\TalkbackCInterface.dll toVCLib\debug


copy bin\release\TalkbackCInterface.dll toVCLib\release


toVCLib\pexports.exe toVCLib\debug\TalkbackCInterface.dll>toVCLib\debug\TalkbackCInterface.def
toVCLib\pexports.exe toVCLib\release\TalkbackCInterface.dll>toVCLib\release\TalkbackCInterface.def

lib /machine:i386 /def:toVCLib\debug\TalkbackCInterface.def

move TalkbackCInterface.lib toVCLib\debug

lib /machine:i386 /def:toVCLib\release\TalkbackCInterface.def
move TalkbackCInterface.lib toVCLib\release
move TalkbackCInterface.exp toVCLib\release

copy bin\debug\OpenAL32.dll ..\..\bin_debug\StandardSDK\avtrace
copy bin\debug\TalkbackCInterface.dll ..\..\bin_debug\StandardSDK\avtrace
copy bin\debug\Talkback.dll ..\..\bin_debug\StandardSDK\avtrace
copy bin\debug\OfferAudioData.dll ..\..\bin_debug\StandardSDK\avtrace
copy bin\debug\offerAudioDataCInterface.dll ..\..\bin_debug\StandardSDK\avtrace

copy bin\release\OpenAL32.dll ..\..\bin_release\StandardSDK\avtrace
copy bin\release\TalkbackCInterface.dll ..\..\bin_release\StandardSDK\avtrace
copy bin\release\Talkback.dll ..\..\bin_release\StandardSDK\avtrace
copy bin\release\OfferAudioData.dll ..\..\bin_release\StandardSDK\avtrace
copy bin\release\offerAudioDataCInterface.dll ..\..\bin_release\StandardSDK\avtrace


copy bin\debug\OpenAL32.dll toOutBin\debug
copy bin\debug\TalkbackCInterface.dll toOutBin\debug
copy bin\debug\Talkback.dll toOutBin\debug
copy bin\debug\OfferAudioData.dll toOutBin\debug
copy bin\debug\offerAudioDataCInterface.dll toOutBin\debug
copy toVCLib\debug\TalkbackCInterface.lib toOutBin\debug

copy bin\release\OpenAL32.dll toOutBin\release
copy bin\release\TalkbackCInterface.dll toOutBin\release
copy bin\release\Talkback.dll toOutBin\release
copy bin\release\OfferAudioData.dll toOutBin\release
copy bin\release\offerAudioDataCInterface.dll toOutBin\release
copy toVCLib\release\TalkbackCInterface.lib toOutBin\release


pause