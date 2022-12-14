#include "cli.hpp"
#include "defaultIO.hpp"
#include "standardIO.hpp"
#include "fileIO.hpp"
#include "socketIO.hpp"
#include "uploadCommand.hpp"
#include "settingsCommand.hpp"
#include "classifyCommand.hpp"
#include "displayCommand.hpp"
#include "downloadCommand.hpp"
#include "matrixCommand.hpp"
#include "settings.hpp"
#include "testAndTrainData.hpp"
#include <iostream>

CLI::CLI(int sock) {
	this->sock = sock;
	this->settings = new Settings();
	this->TATData = new TestAndTrainData();
	commands.push_back(new UploadFileCMD(new SocketIO(sock), TATData));
	commands.push_back(new AlgoSettingsCMD(new SocketIO(sock), settings));
	commands.push_back(new ClassifyDataCMD(new SocketIO(sock), settings, TATData));
	commands.push_back(new DisplayResultsCMD(new SocketIO(sock), TATData));
	commands.push_back(new DownloadResultsCMD(new SocketIO(sock), TATData));
	commands.push_back(new AlgorithmConfusionMatrixCMD(new SocketIO(sock), settings, TATData));
}

CLI::~CLI() {
	delete this->settings;
	delete this->TATData;
}

void CLI::start() {
	SocketIO sio(this->sock);
	while (true) {
		int input = 0;
		sio.write("Welcome to the KNN Classifier Server. Please choose an option\n");
		for (int i = 0; i < commands.size(); i++) {
			sio.write(std::to_string(i + 1) +". " + (commands[i]->description) + "\n");
		}
		sio.write("7. exit\n");
		while (input < 1 || input > 7) {
			try {
				input = std::stoi(sio.read());
			} catch (const std::exception&) {
				sio.write("Option unavailable! Please try again\n");
				continue;
			}
		}
		if (input == 7) {
			return;
		}
		commands[input - 1]->execute();
	}
}