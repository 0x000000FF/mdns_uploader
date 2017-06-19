; 该脚本使用 HM VNISEdit 脚本编辑器向导产生

; 安装程序初始定义常量
!define PRODUCT_NAME "mostfun printer plug"
!define PRODUCT_VERSION "beta 0.0.1"
!define PRODUCT_PUBLISHER "mostfun,CD, Inc."
!define PRODUCT_WEB_SITE "http://mostfun.cn/"
!define PRODUCT_DIR_REGKEY "Software\Microsoft\Windows\CurrentVersion\App Paths\mostfun_upload.exe"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"

SetCompressor /SOLID lzma

; ------ MUI 现代界面定义 (1.67 版本以上兼容) ------
!include "MUI.nsh"

; MUI 预定义常量
!define MUI_ABORTWARNING
!define MUI_ICON "D:\mostfunico.ico"
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall.ico"

; 语言选择窗口常量设置
!define MUI_LANGDLL_REGISTRY_ROOT "${PRODUCT_UNINST_ROOT_KEY}"
!define MUI_LANGDLL_REGISTRY_KEY "${PRODUCT_UNINST_KEY}"
!define MUI_LANGDLL_REGISTRY_VALUENAME "NSIS:Language"

; 欢迎页面
!insertmacro MUI_PAGE_WELCOME
; 许可协议页面
!insertmacro MUI_PAGE_LICENSE "LICENCE.txt"
; 安装目录选择页面
!insertmacro MUI_PAGE_DIRECTORY
; 安装过程页面
!insertmacro MUI_PAGE_INSTFILES
; 安装完成页面
!insertmacro MUI_PAGE_FINISH

; 安装卸载过程页面
!insertmacro MUI_UNPAGE_INSTFILES

; 安装界面包含的语言设置
!insertmacro MUI_LANGUAGE "English"
!insertmacro MUI_LANGUAGE "SimpChinese"

; 安装预释放文件
!insertmacro MUI_RESERVEFILE_LANGDLL
!insertmacro MUI_RESERVEFILE_INSTALLOPTIONS
; ------ MUI 现代界面定义结束 ------

Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "Setup.exe"
InstallDir "$PROGRAMFILES\mostfun"
InstallDirRegKey HKLM "${PRODUCT_UNINST_KEY}" "UninstallString"
ShowInstDetails show
ShowUnInstDetails show
BrandingText "mostfun"

Section "MainSection" SEC01
  SetOutPath "$INSTDIR"
  SetOverwrite ifnewer
  File "Qt5Widgets.dll"
  CreateDirectory "$SMPROGRAMS\mostfun printer plug"
  CreateShortCut "$SMPROGRAMS\mostfun printer plug\mostfun printer plug.lnk" "$INSTDIR\mostfun_upload.exe"
  CreateShortCut "$DESKTOP\mostfun printer plug.lnk" "$INSTDIR\mostfun_upload.exe"
  File "Qt5Svg.dll"
  File "Qt5Network.dll"
  File "Qt5Gui.dll"
  File "Qt5Core.dll"
  File "opengl32sw.dll"
  File "mostfun_upload.exe"
  File "LICENCE.txt"
  File "libGLESV2.dll"
  File "libEGL.dll"
  File "D3Dcompiler_47.dll"
  File "mostfunico.ico"
  
  SetOutPath "$INSTDIR\bearer"
  File ".\bearer\qgenericbearer.dll"
  File ".\bearer\qnativewifibearer.dll"
  
  SetOutPath "$INSTDIR\iconengines"
  File ".\iconengines\qsvgicon.dll"
  
  SetOutPath "$INSTDIR\imageformats"
  File ".\imageformats\qgif.dll"
  File ".\imageformats\qicns.dll"
  File ".\imageformats\qico.dll"
  File ".\imageformats\qjpeg.dll"
  File ".\imageformats\qsvg.dll"
  File ".\imageformats\qtga.dll"
  File ".\imageformats\qtiff.dll"
  File ".\imageformats\qwbmp.dll"
  File ".\imageformats\qwebp.dll"
  
  SetOutPath "$INSTDIR\platforms"
  File ".\platforms\qwindows.dll"
  
  SetOutPath "$INSTDIR\translations"
  File ".\translations\qt_ca.qm"
	File ".\translations\qt_cs.qm"
	File ".\translations\qt_de.qm"
	File ".\translations\qt_en.qm"
	File ".\translations\qt_fi.qm"
	File ".\translations\qt_fr.qm"
	File ".\translations\qt_he.qm"
	File ".\translations\qt_hu.qm"
	File ".\translations\qt_it.qm"
	File ".\translations\qt_ja.qm"
	File ".\translations\qt_ko.qm"
	File ".\translations\qt_lv.qm"
	File ".\translations\qt_pl.qm"
	File ".\translations\qt_ru.qm"
	File ".\translations\qt_sk.qm"
	File ".\translations\qt_uk.qm"
  
SectionEnd

Section -Post
  WriteUninstaller "$INSTDIR\uninst.exe"
  WriteRegStr HKLM "${PRODUCT_DIR_REGKEY}" "" "$INSTDIR\mostfun_upload.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayIcon" "$INSTDIR\mostfun_upload.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
  ;witch item shows in mycomputer
  WriteRegStr HKLM "SOFTWARE\Classes\CLSID\{2D744CA6-144C-4E07-B42E-85BBAC321C43}" "" "mostfun"
  WriteRegStr HKLM "SOFTWARE\Classes\CLSID\{2D744CA6-144C-4E07-B42E-85BBAC321C43}" "LocalizedString" "mostfun"
  WriteRegStr HKLM "SOFTWARE\Classes\CLSID\{2D744CA6-144C-4E07-B42E-85BBAC321C43}" "InfoTip" "mostfun panel"
  WriteRegStr HKLM "SOFTWARE\Classes\CLSID\{2D744CA6-144C-4E07-B42E-85BBAC321C43}" "TileInfo" "prop:System.ItemAuthors"
  WriteRegStr HKLM "SOFTWARE\Classes\CLSID\{2D744CA6-144C-4E07-B42E-85BBAC321C43}" "System.ItemAuthors" "mostfun panel"
  WriteRegStr HKLM "SOFTWARE\Classes\CLSID\{2D744CA6-144C-4E07-B42E-85BBAC321C43}\DefaultIcon" "" "$INSTDIR\mostfunico.ico"
  WriteRegStr HKLM "SOFTWARE\Classes\CLSID\{2D744CA6-144C-4E07-B42E-85BBAC321C43}\InprocServer32" "" "shdocvw.dll"
  WriteRegStr HKLM "SOFTWARE\Classes\CLSID\{2D744CA6-144C-4E07-B42E-85BBAC321C43}\InprocServer32" "ThreadingModel" "Apartment"
  WriteRegStr HKLM "SOFTWARE\Classes\CLSID\{2D744CA6-144C-4E07-B42E-85BBAC321C43}\Instance" "" ""
  WriteRegStr HKLM "SOFTWARE\Classes\CLSID\{2D744CA6-144C-4E07-B42E-85BBAC321C43}\Instance" "CLSID" "{0AFACED1-E828-11D1-9187-B532F1E9575D}"
  WriteRegStr HKLM "SOFTWARE\Classes\CLSID\{2D744CA6-144C-4E07-B42E-85BBAC321C43}\Instance\InitPropertyBag" "Target" "D:\\"
  WriteRegStr HKLM "SOFTWARE\Classes\CLSID\{2D744CA6-144C-4E07-B42E-85BBAC321C43}\shell\Open\Command" "" "$INSTDIR\mostfun_upload.exe"
  ;item shows in mycomputer
  WriteRegStr HKCU "SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\MyComputer\NameSpace\{2D744CA6-144C-4E07-B42E-85BBAC321C43}" "" ""
  ;right click menu
  WriteRegStr HKCR "*\shell\mostfun" "" "Upload to mostfunPro"
  WriteRegStr HKCR "*\shell\mostfun" "icon" "$INSTDIR\mostfunico.ico"
  WriteRegStr HKCR "*\shell\mostfun\command" "" "$INSTDIR\mostfun_upload.exe %l"
SectionEnd

#-- 根据 NSIS 脚本编辑规则，所有 Function 区段必须放置在 Section 区段之后编写，以避免安装程序出现未可预知的问题。--#

Function .onInit
  !insertmacro MUI_LANGDLL_DISPLAY
FunctionEnd

/******************************
 *  以下是安装程序的卸载部分  *
 ******************************/

Section Uninstall
  Delete "$INSTDIR\uninst.exe"
  Delete "$INSTDIR\D3Dcompiler_47.dll"
  Delete "$INSTDIR\libEGL.dll"
  Delete "$INSTDIR\libGLESV2.dll"
  Delete "$INSTDIR\LICENCE.txt"
  Delete "$INSTDIR\mostfun_upload.exe"
  Delete "$INSTDIR\opengl32sw.dll"
  Delete "$INSTDIR\Qt5Core.dll"
  Delete "$INSTDIR\Qt5Gui.dll"
  Delete "$INSTDIR\Qt5Network.dll"
  Delete "$INSTDIR\Qt5Svg.dll"
  Delete "$INSTDIR\Qt5Widgets.dll"
  Delete "$INSTDIR\mostfunico.ico"
	Delete "$INSTDIR\bearer\qgenericbearer.dll"
	Delete "$INSTDIR\bearer\qnativewifibearer.dll"
	Delete "$INSTDIR\iconengines\qsvgicon.dll"
	Delete "$INSTDIR\imageformats\qgif.dll"
	Delete "$INSTDIR\imageformats\qicns.dll"
	Delete "$INSTDIR\imageformats\qico.dll"
	Delete "$INSTDIR\imageformats\qjpeg.dll"
	Delete "$INSTDIR\imageformats\qsvg.dll"
	Delete "$INSTDIR\imageformats\qtga.dll"
	Delete "$INSTDIR\imageformats\qtiff.dll"
	Delete "$INSTDIR\imageformats\qwbmp.dll"
	Delete "$INSTDIR\imageformats\qwebp.dll"
	Delete "$INSTDIR\platforms\qwindows.dll"
	Delete "$INSTDIR\translations\qt_ca.qm"
	Delete "$INSTDIR\translations\qt_cs.qm"
	Delete "$INSTDIR\translations\qt_de.qm"
	Delete "$INSTDIR\translations\qt_en.qm"
	Delete "$INSTDIR\translations\qt_fi.qm"
	Delete "$INSTDIR\translations\qt_fr.qm"
	Delete "$INSTDIR\translations\qt_he.qm"
	Delete "$INSTDIR\translations\qt_hu.qm"
	Delete "$INSTDIR\translations\qt_it.qm"
	Delete "$INSTDIR\translations\qt_ja.qm"
	Delete "$INSTDIR\translations\qt_ko.qm"
	Delete "$INSTDIR\translations\qt_lv.qm"
	Delete "$INSTDIR\translations\qt_pl.qm"
	Delete "$INSTDIR\translations\qt_ru.qm"
	Delete "$INSTDIR\translations\qt_sk.qm"
	Delete "$INSTDIR\translations\qt_uk.qm"

  Delete "$DESKTOP\mostfun printer plug.lnk"
  Delete "$SMPROGRAMS\mostfun printer plug\mostfun printer plug.lnk"

  RMDir "$SMPROGRAMS\mostfun printer plug"

  RMDir "$INSTDIR"

  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
  DeleteRegKey HKLM "${PRODUCT_DIR_REGKEY}"
  DeleteRegKey HKCR ".gcode\shell\mostfun"
  DeleteRegKey HKCU "SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\MyComputer\NameSpace\{2D744CA6-144C-4E07-B42E-85BBAC321C43}"
  DeleteRegKey HKLM "SOFTWARE\Classes\CLSID\{2D744CA6-144C-4E07-B42E-85BBAC321C43}"
  SetAutoClose true
SectionEnd

#-- 根据 NSIS 脚本编辑规则，所有 Function 区段必须放置在 Section 区段之后编写，以避免安装程序出现未可预知的问题。--#

Function un.onInit
!insertmacro MUI_UNGETLANGUAGE
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "您确实要完全移除 $(^Name) ，及其所有的组件？" IDYES +2
  Abort
FunctionEnd

Function un.onUninstSuccess
  HideWindow
  MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) 已成功地从您的计算机移除。"
FunctionEnd
