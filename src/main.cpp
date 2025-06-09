/*
 * main.cpp
 *
 *  Created on: Apr 8, 2020
 *      Author: User
 */

#include "es-converter.h"
#include "nif_converter.h"


const std::string PLUGIN_EXTENSION = ".esp";


int main(int argc, char* const argv[], char* const envp[]) {


		std::cout << std::endl << "============================================================" << std::endl;
		std::string s2 = "WARNING: Do not distribute any files produced by this software in any format. Please see Readme.txt for more information.";
		std::cout << s2 << std::endl;
		std::cout << "============================================================" << std::endl << std::endl;;


		if (argc != 4) {
			std::cout << "Please provide plugin name and input/output folders. Please see Readme.txt for instructions." << std::endl;
			return 1;
		}

		char* pluginName = argv[1];
		char* inFolder = argv[2];
		char* outFolder = argv[3];

		if (strlen(pluginName) == 0) {
			std::cout << "Plugin name is required." << std::endl;
			return 1;
		}

		if (strcmp(inFolder, outFolder) == 0) {
			std::cout << "Input and output folders can not be same." << std::endl;
			return 1;
		}

		if (!std::experimental::filesystem::exists(inFolder) || !std::experimental::filesystem::exists(outFolder)) {
			std::cout << "Can not find input/output folder(s)." << std::endl;
			return 1;
		}


		const std::string IN_FOLDER = std::experimental::filesystem::absolute(std::string(inFolder)).u8string().c_str();
		const std::string OUT_FOLDER = std::experimental::filesystem::absolute(std::string(outFolder)).u8string().c_str();


		// clean previous conversion files
		std::experimental::filesystem::remove_all(OUT_FOLDER + "\\Data\\data000");
		std::experimental::filesystem::remove(OUT_FOLDER + "\\Data\\" + pluginName + PLUGIN_EXTENSION);
		std::experimental::filesystem::remove(OUT_FOLDER + "\\Data\\" + pluginName + " - Main.ba2");
		std::experimental::filesystem::remove(OUT_FOLDER + "\\Data\\" + pluginName + " - Textures.ba2");



		/*Nif Converter*/
		std::cout << "Converting NIF files..." << std::endl;

		const std::string nifListFileName = std::string(pluginName)  + ".txt";
		std::ifstream nifList(nifListFileName.c_str());
		for( std::string line; getline( nifList, line ); )
		{


			std::string nifInputFile = IN_FOLDER + "\\Data\\Meshes\\" + line;
			std::string nifOutputFile = OUT_FOLDER + "\\Data\\data000\\Meshes\\" + line;

			if (std::experimental::filesystem::exists(nifInputFile)) {

				std::experimental::filesystem::path dir(OUT_FOLDER + "\\Data\\data000\\Meshes\\" + line);
				if (!std::experimental::filesystem::exists(dir.parent_path())) {
					std::experimental::filesystem::create_directories(dir.parent_path());
				}

				try {
					//std::cout << "Converting: " << nifInputFile << std::endl;
					nif::processNif(nifInputFile.c_str(), nifOutputFile.c_str());
				}
				catch (...) {
					std::cout << "Failed to convert: " << nifInputFile << std::endl;
					std::ofstream file("nif_converter_errors.txt", std::ios_base::app);
					file << "Failed to convert: " << nifInputFile << std::endl;
					file.close();
				}



			}

		}
		std::cout << "Done converting NIF files..." << std::endl;
		/*Nif Converter*/




		/*elric*/
		const std::string ELRIC_COMMAND = " \" \""+ OUT_FOLDER +"\\Tools\\Elric\\Elrich.exe\" \"" + OUT_FOLDER + "\\Tools\\Elric\\Settings\\PCMeshes.esf\" -ElricOptions.ConvertTarget=\"" + OUT_FOLDER + "\\Data\\data000\\Meshes\" -ElricOptions.OutputDirectory=\"" + OUT_FOLDER + "\\Data\\data000\\Meshes\" -ElricOptions.UseFilterScript=false -ElricOptions.CloseWhenFinished=true\" \"";

		std::cout << "Optimizing NIF files using Elric..." << std::endl;
		if (system(ELRIC_COMMAND.c_str()) == 0) {
			std::cout << "Done optimizing NIF files..." << std::endl;
		} else {
			std::cout << "Failed to optimize meshes.." << std::endl;
			return 1;
		}
		/*elric*/



		// convert plugin
		esf::convert(pluginName, PLUGIN_EXTENSION, IN_FOLDER + "\\Data", OUT_FOLDER + "\\Data\\data000");


		// archive everything
		const std::string ARCHIVE2_COMMAND_TEXTURES = " \" \"" + OUT_FOLDER + "\\Tools\\Archive2\\Archive2.exe\" \"" + IN_FOLDER + "\\Data\\Textures\"  -c=\"" + OUT_FOLDER + "\\Data\\data000\\" + pluginName + " - Textures.ba2\" -f=DDS -q \"";
		std::cout << "Archiving textures..." << std::endl;
		//std::cout << ARCHIVE2_COMMAND_TEXTURES << std::endl;
		if (system(ARCHIVE2_COMMAND_TEXTURES.c_str()) == 0) {
			std::cout << "Done archiving textures..." << std::endl;
		} else {
			std::cout << "Failed to archive textures..." << std::endl;
			return 1;
		}

		const std::string ARCHIVE2_COMMAND_MAIN = " \" \"" + OUT_FOLDER + "\\Tools\\Archive2\\Archive2.exe\" \"" + OUT_FOLDER + "\\Data\\data000\\Meshes, " + OUT_FOLDER  + "\\Data\\data000\\LODSettings\"  -c=\"" + OUT_FOLDER + "\\Data\\data000\\" + pluginName + " - Main.ba2\" -r=\""+ OUT_FOLDER + "\\Data\\data000\" -q \"";
		std::cout << "Archiving meshes..." << std::endl;
		//std::cout << ARCHIVE2_COMMAND_MAIN << std::endl;
		if (system(ARCHIVE2_COMMAND_MAIN.c_str()) == 0) {
			std::cout << "Done archiving meshes..." << std::endl;
		} else {
			std::cout << "Failed to archive meshes..." << std::endl;
			return 1;
		}

		//clean up
		std::experimental::filesystem::rename(OUT_FOLDER + "\\Data\\data000\\" + pluginName + PLUGIN_EXTENSION, OUT_FOLDER + "\\Data\\" + pluginName + PLUGIN_EXTENSION);
		std::experimental::filesystem::rename(OUT_FOLDER + "\\Data\\data000\\" + pluginName + " - Main.ba2", OUT_FOLDER + "\\Data\\" + pluginName + " - Main.ba2");
		std::experimental::filesystem::rename(OUT_FOLDER + "\\Data\\data000\\" + pluginName + " - Textures.ba2", OUT_FOLDER + "\\Data\\" + pluginName + " - Textures.ba2");

		std::experimental::filesystem::remove_all(OUT_FOLDER + "\\Data\\data000");

		std::cout << "Conversion is completed successfully." << std::endl;



	return 0;
}
