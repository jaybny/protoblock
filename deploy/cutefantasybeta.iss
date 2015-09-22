; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "Trading Football"
#define MyAppVersion "2015 1.0.3"
#define MyAppPublisher "Satoshi Fantasy LLC"
#define MyAppURL "http://trading.football"
#define MyAppExeName "tradingfootball.exe"


[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{79913283-A35B-4274-927C-1B52D286D939}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultGroupName={#MyAppName}
OutputDir=..\installer
OutputBaseFilename=tradingfootball-setup
Compression=lzma
SolidCompression=yes
WizardImageFile=TRADINGFOOTBALL.bmp
PrivilegesRequired=none
DefaultDirName={localappdata}\tradingfootball
[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
; NOTE: Don't use "Flags: ignoreversion" on any shared system files
Source: "tradingfootball.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "storage\GenesisTransition-Tr-Transaction.txt"; DestDir: "{app}\storage"; Flags: ignoreversion
Source: "vcredist_x64.exe"; DestDir: "{tmp}"; Flags: ignoreversion
Source: "libeay32.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "msvcp120.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "msvcr120.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "Qt5Core.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "Qt5Gui.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "Qt5Network.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "Qt5Widgets.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "ssleay32.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "vcredist_x64.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "platforms\qwindows.dll"; DestDir: "{app}\platforms"
Source: "imageformats\qgif.dll"; DestDir: "{app}\imageformats"; Flags: ignoreversion
Source: "bearer\qgenericbearer.dll"; DestDir: "{app}\bearer"
Source: "bearer\qnativewifibearer.dll"; DestDir: "{app}\bearer"

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: "{tmp}\vcredist_x64.exe"; Parameters: "/q"; StatusMsg: "Installing Microsoft Visual C++ 2010 x64 Redistributable..."
Filename: {app}\{#MyAppExeName}; Flags: nowait postinstall skipifsilent 64bit RunAsOriginalUser; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; 

[Dirs]
Name: "{app}\bearer"
Name: "{app}\imageformats"
Name: "{app}\platforms"
Name: "{app}\storage"

[InstallDelete]
Type: filesandordirs; Name: "{app}\storage\index"
Type: filesandordirs; Name: "{app}\storage\block"
Type: filesandordirs; Name: "{app}\cutefantasy.log"

[Code]
function IsRegularUser(): Boolean;
begin
Result := not (IsAdminLoggedOn or IsPowerUserLoggedOn);
end;

function DefDirRoot(Param: String): String;
begin
if IsRegularUser then
Result := ExpandConstant('{localappdata}')
else
Result := ExpandConstant('{pf}')
end;