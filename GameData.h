//
//  GameData.h
//  Project
//
//  Created by Richard on 2023/11/21.
//

#ifndef GameData_h
#define GameData_h
#define Q 16

const char* FontAddr[] = {"./Font/lazy.ttf", "./Font/CaviarDreams.ttf", "./Font/CaviarDreams_Italic.ttf", "./Font/CaviarDreams_BoldItalic.ttf", "./Font/Caviar_Dreams_Bold.ttf"};
const char* SoundEffectAddr[] = {"./SoundEffect/hitsound.mp3"};
const char* NoteAddr[] = {"./Element/hit.png", "./Element/hold.png"};
const char* ButtonAddr[] = {"./Element/continue.png", "./Element/close.png", "./Element/judgeline.png", "./Element/judgeline.png", "./Element/judgeline.png", "./Element/judgeline.png"};
const char* JudgelineAddr[] = {"./Element/judgeline.png", "./Element/judgeline.png", "./Element/judgeline.png", "./Element/judgeline.png"};
const char* SongfileAddr[] = {"./Element/judgeline.png"};
const char* ScreenButton[] = {"./Song/button_Easy.png","./Song/button_Hard.png","./Song/button_Insane.png","./Song/button_Easy_Selected.png","./Song/button_Hard_Selected.png","./Song/button_Insane_Selected.png"};
const char* MaingameMusicAddr[] = {"./Music/M000.mp3"};
const char* PreviewMusicAddr[] = {"./Music/MP000.mp3", "./Music/MD.mp3", "./Music/MD.mp3"};
const char* BackgroundAddr[] = {"./Background/title.bmp", "./Background/selecting.bmp", "./Background/maingame.bmp", "./Background/result.bmp"};
const char* BeatmapAddr[][3] = {{"./Beatmap/001.1.txt", "./Beatmap/001.2.txt", "./Beatmap/001.3.txt"}};

int BEATMAPPARAMS_TOTAL = 9;

#endif /* GameData_h */
