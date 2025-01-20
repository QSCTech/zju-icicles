setPreference -pref AutoSignature:FALSE
setPreference -pref KeepSVF:FALSE
setPreference -pref ConcurrentMode:FALSE
setPreference -pref UseHighz:FALSE
setPreference -pref svfUseTime:FALSE
loadProjectFile -file "E:/Xilinx/SP2_prj/SP2_prj.ipf"
setMode -ss
setMode -sm
setMode -hw140
setMode -spi
setMode -acecf
setMode -acempm
setMode -pff
setMode -bs
setMode -bs
setMode -bs
setCable -port auto
Verify -p 1 
Program -p 1 -defaultVersion 0 
saveProjectFile -file "E:/Xilinx/SP2_prj/SP2_prj.ipf"
