#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "BreakObj.h"

namespace GameLib {
	class Sprite;
}

struct Note
{
	float pos = 0.0f;
	float note_before_sound = 0.0f;
	double perfect_pos = 0.0;
	bool Flag = false;

	float velocity = 0.0f;
	float degree = 0.0f;
	float degree_acc = 0.0f;
	GameLib::Sprite* sprite = nullptr;

	char object_filter = '0';

	breakObj obj;
};


struct MusicDataOption
{
	std::string song_name;
	std::string song_path;
	int bpm;
	float offset;
	bool isStart;

	MusicDataOption() :
		song_name(),
		song_path(),
		bpm(0),
		offset(0),
		isStart(false)
	{}
};


class NoteManager
{
public:
	NoteManager();
	~NoteManager();

	void AddNote(int, int, int, int, MusicDataOption*, char);

	void InitNotes();
	void UpdateNotes(float, float, float);
	void DrawNotes();

	double getNoteTiming(unsigned int, unsigned int);

	static constexpr float JUDGE_START = -200.0f;
	static constexpr float JUDGE_LINE = 500.0f;
	static constexpr float JUDGE_SIZE = JUDGE_LINE - JUDGE_START;
	static constexpr float WINDOW_H = 960;
private:
	void JudgeFlag(float, Note&);
private:
	std::vector<std::vector<Note>> m_note_2d;
	std::vector<unsigned int> m_notes_size;
};


class MusicData
{
public:
	MusicData() = delete;
	MusicData(const MusicData&) = delete;
	MusicData& operator=(const MusicData&) = delete;


	MusicData(const std::string&);
	~MusicData();

	bool GetFileData();
	bool GetFileData(const std::string&);
	void Load_MusicOptions();
	void Load_NotesData();

	const std::stringstream& getOptionStream() const { return m_file_options; }
	const std::stringstream& getDataStream() const { return m_file_data; }

	const MusicDataOption& getOptions() const { return m_options; }
	NoteManager& getNoteManager() const { return *m_noteManager; }

private:
	std::string m_file_name;
	std::ifstream m_file;

	std::stringstream m_file_options;
	std::stringstream m_file_data;

	NoteManager* m_noteManager;
	MusicDataOption m_options;
};
