F3NV to F4 Converter

This is a non-commercial fan project for educational and demonstration purposes only. Source code is under the GNU General Public License 3 (GPL3).

This software DOES NOT CONTAIN any BETHESDA or any other 3rd party assets. All assets are generated/converted on user's PC by a user running this software.

This tool creates a mod (.esp and .ba2 files) for Fallout 4 from vanilla Fallout 3/NV assets. You can explore capital wasteland and Mojave. No npcs, creatures, quests etc, only landscape, architecture, interiors, furniture and junk. 

LEGAL WARNING
Do not distribute any files produced by this software in any format. All converted assets remain the property of Bethesda Softworks.

DISCLAIMER
This software is provided "AS IS", with ABSOLUTELY NO WARRANTY. Use it at your own risk.

You have to own and install both source (Fallout 3 or NV) and target (Fallout 4) games.

REQUIRED SOFTWARE:
1. Fallout 4 game. https://store.steampowered.com/app/377160/Fallout_4/
2. Fallout 3 or Fallout NV game. https://store.steampowered.com/app/22300/Fallout_3/
3. Creation kit (only for Elric and Archive2 tools). No editing skills are required. https://bethesda.net/en/game/bethesda-launcher
4. B.A.E - Bethesda archive extractor. https://www.nexusmods.com/fallout4/mods/78/?
5. xLODGen for lod generation. https://forum.step-project.com/topic/13451-xlodgen-terrain-lod-beta-for-fnv-fo3-fo4-fo4vr-tes5-sse-tes5vr-enderal/


CONVERSION INSTRUCTIONS (Relace 3 with NV for New Vegas):

1. Download and Install Creation Kit using Bethesda Launcher.
2. Download B.A.E.
3. Download xLODGen.

4. Create "CONV" folder on your Desktop.
5. Create "FO3" and "FO4" folders inside "CONV" folder.
6. Create "Data" folders inside "FO3" and "FO4" folders.

7. Copy Fallout3.esm from "..\Steam\..\Fallout 3\Data" folder to "Desktop\CONV\FO3\Data" folder.
8. Extract lodsettings folder from "..\Steam\..\Fallout 3\Data\Fallout - Misc.bsa" to "Desktop\CONV\FO3\Data\lodsettings" using B.A.E
9. Extract Meshes folder from "..\Steam\..\Fallout 3\Data\Fallout - Meshes.bsa" to "Desktop\CONV\FO3\Data\Meshes" using B.A.E
10. Extract Textures folder from "..\Steam\..\Fallout 3\Data\Fallout - Textures.bsa" to "Desktop\CONV\FO3\Data\Textures" using B.A.E

11. Copy Archive2 folder from "..\Steam\..\Fallout 4\Tools" to "Desktop\CONV\FO4\Tools"
12. Copy Elric folder from "..\Steam\..\Fallout 4\Tools" to "Desktop\CONV\FO4\Tools"

13. Make sure your CONV\FO3 and CONV\FO4 folders have following structure: 
CONV\
| - FO3\
|   | - Data\
|       | - lodsettings\
|       | - Meshes\
|       | - Textures\
|       | - Fallout3.esm 
|
| - FO4\
|   | - Data\ (converted files will be placed here)
|   | - Tools\
|       | - Archive2\
|       | - Elric\

14. Open windows command line and execute from tool's location:

fo3nv2fo4.exe "Fallout3" "C:\Users\your-user-name\Desktop\CONV\FO3" "C:\Users\your-user-name\Desktop\CONV\FO4"
Do not interfere with conversion process. Elric window will pop up during the process, do not press anything, let it finish, it will close automatically.  It might take some time, depending on performance of your PC.
Also there will be Archive2 complains about skipping some files. Just ignore. 

15. After conversion is finished make sure "Desktop\CONV\FO4\Data" folder has following files:
Fallout3.esp
Fallout3 - Main.ba2
Fallout3 - Textures.ba2

Now you have two options:

Option A: {
Move content of "Desktop\CONV\FO4\Data" (3 files above) to "..\Steam\..\Fallout 4\Data" folder and enable Fallout3.esp in the Mod manager you are using.
}
Option B: {
Zip "Data" folder located inside "Desktop\CONV\FO4" and name it Fallout3.zip. Should look like this:
Fallout3.zip
| - Data\
| - Fallout3.esp
| - Fallout3 - Main.ba2
| - Fallout3 - Textures.ba2
Move Fallout3.zip wherever you want and install it using Mod manager of your choice.
}

16. Make sure everything works before generation LOD. Launch Fallout 4, load any save you have, open terminal and run: "coc xxxVault101exterior" ("coc xxxGoodSprings" for New Vegas). 

17. Generating LOD will take a lot of resources of your PC. You may consider skipping this step if your PC is not powerful enough. Please see xLODGen download page for more info.
Open xLODGen, un-check everything on the left panel and check all items starting with xxx. Check "Objects LOD" and "Terrain LOD" on the right panel. Leave everything else as is. Press Generate button. 

18. Purge Desktop\CONV folder.

19. Done.

HOW TO PLAY:
All Fallout 3/NV editor_names have xxx prefix after conversion. 
Launch Fallout 4, load any save you have, open terminal and run: "coc xxxVault101exterior" for Fallout 3 and "coc xxxGoodSprings" for New Vegas. 

Important known issues:
1. Player unable climb stairs. You have to jump.
2. Megaton s landscape is shifted down. Use coc xxxMegaton01 to enter Megaton.
3. Some places inaccessible. Like missing Rivet City bridge. Use tcl command.