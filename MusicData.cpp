#include "MusicData.h"
#include "./GameLib/game_lib.h"
#include <random>

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// NoteManager class /////////////////////////////////////////

NoteManager::NoteManager()
{
	m_note_2d.resize(2);
	m_notes_size.resize(2);

	fill(m_notes_size.begin(), m_notes_size.end(), 0);
}

NoteManager::~NoteManager()
{
}

void NoteManager::AddNote(int col, int row, int num, int length, MusicDataOption* p, char sprite_index)
{
	Note note{};
	note.pos = -100.0f;
	note.perfect_pos = 60.0 * 4 * (row + (double)num / length) / p->bpm - p->offset;
	note.Flag = false;
	note.velocity = 1.0f;

    auto load_sprite = [](char sprite_index, Note& note)
        {
            switch (sprite_index)
            {
            case '1':
                note.sprite = GameLib::sprite_load(L"./Data/Images/bin.png");
                break;
            case '2':
                note.sprite = GameLib::sprite_load(L"./Data/Images/hako.png");
                break;
            case '3':
                note.sprite = GameLib::sprite_load(L"./Data/Images/taru_2.png");
                break;
            default:
                note.sprite = nullptr;
                break;
            }
        };
    load_sprite(sprite_index, note);
    
    m_note_2d[col].push_back(note);
    m_notes_size[col]++;
}

void NoteManager::InitNotes()
{
	for (auto& col : m_note_2d)
	{
		for (auto& row : col)
		{
			if (!row.Flag)
				row.Flag = true;

			auto acc = []()
				{
					std::random_device rd;
					std::mt19937 gen(rd());
					std::uniform_real_distribution<> dist(-5.0, 5.0);
					return static_cast<float>(dist(gen));
				};
			row.degree_acc = acc();
		}
	}
}

void NoteManager::UpdateNotes(float current_time, float keydown_time)
{
	for (auto& col : m_note_2d)
	{
		for (auto& row : col)
		{
			if (row.Flag && ((row.perfect_pos - current_time) <= 1.0f))
			{
				// 加速度上昇
				{
					if (row.velocity <= 2.0f)
						row.velocity += 0.025f;
				}

				// 回転値
				{
					row.degree += row.degree_acc;
				}

				// ノートの座標　= 終点から始点への方向 * ((叩かれる時間 - 現在の時間) * レーンの長さ * 速度) + 終点
				row.pos = -1.0f * (((float)row.perfect_pos - current_time) * JUDGE_SIZE * row.velocity) + JUDGE_LINE;

				// 範囲外になったらフラグをfalseにする
				{
					if (WINDOW_H < row.pos && 0.3 < current_time - row.perfect_pos)
						row.Flag = false;
				}

			}
			JudgeFlag(keydown_time, row);
		}
	}
}

void NoteManager::JudgeFlag(float keydonw_time, Note& note)
{
	if (fabsf((float)note.perfect_pos - keydonw_time) <= 0.09)
		note.Flag = false;
}

void NoteManager::DrawNotes()
{
	int i = 0;
	for (auto& col : m_note_2d)
	{
		i++;
		for (auto& row : col)
		{
			if (row.Flag)
			{
				float radian = DirectX::XMConvertToRadians(row.degree);
				GameLib::sprite_render(row.sprite, 300.f * i, row.pos,
					0.4f, 0.4f, 0.0f, 0.0f, 512.0f, 512.0f, 256.0f, 256.0f, radian);
			}
		}
	}      

	GameLib::primitive::line({ 0.0f, JUDGE_LINE }, { 1280.0f, JUDGE_LINE }, { 1.0f, 1.0f, 1.0f, 1.0f });
}

double NoteManager::getNoteTiming(unsigned int col, unsigned int num)
{
	if (col > 2) return -1.0;
	if (num > m_notes_size[col] - 1) return -1.0;

	return m_note_2d[col][num].perfect_pos;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// MusicData class /////////////////////////////////////////

MusicData::MusicData(const std::string& filename) :
	m_file(),
	m_file_name(),
	m_file_options(),
	m_file_data(),
	m_noteManager(nullptr),
	m_options()
{
	m_noteManager = new NoteManager;
	m_file_name = filename;
	GetFileData();
}

bool MusicData::GetFileData()
{
	// テキストファイル読み込み
	{
		m_file.open(m_file_name, std::ios::in);
		if (!m_file)
		{
			return false;
		}
	}
	// テキストファイルからオプションを読み込み
	{
		string music_option_data;
		getline(m_file, music_option_data, ',');
		m_file_options << music_option_data;

		Load_MusicOptions();
	}
	// 譜面データに移動
	m_file.seekg(2, ios::cur);
	// テキストファイルから譜面を読み込み
	{
		string music_notes;
		getline(m_file, music_notes, '.');
		m_file_data << music_notes;
		Load_NotesData();
	}

	return true;
}

bool MusicData::GetFileData(const string& filename)
{
	// テキストファイル読み込み
	{
		m_file_name = filename;
		m_file.open(m_file_name, std::ios::in);
	}
	// テキストファイルからオプションの読み込み
	{
		string music_option_data;
		getline(m_file, music_option_data, ',');
		m_file_options << music_option_data;

		Load_MusicOptions();
	}
	// 譜面データに移動
	m_file.seekg(2, ios::cur);

	// テキストファイルから譜面の読み込み
	{
		string music_notes;
		getline(m_file, music_notes, '.');
		m_file_data << music_notes;
		Load_NotesData();
	}

	return true;
}

void MusicData::Load_MusicOptions()
{
	string row_str;
	while (getline(m_file_options, row_str))
	{
		if (row_str == "#START")
		{
			m_options.isStart = true;
			break;
		}

		stringstream data(row_str);
		string name;
		getline(data, name, ':');
		if (name == "TITLE")
			data >> m_options.song_name;
		else if (name == "BPM")
			data >> m_options.bpm;
		else if (name == "OFFSET")
			data >> m_options.offset;
		else if (name == "WAVE")
			data >> m_options.song_path;
	}
}

void MusicData::Load_NotesData()
{
    string data;
    for (int row = 0; getline(m_file_data, data); row++)
    {
        stringstream data_stream(data);
        string separate_data;
        for (int col = 0; getline(data_stream, separate_data, ','); col++)
        {
            int length = (int)separate_data.size();
            for (int i = 0; i < length; i++)
            {
                if ('1' <= separate_data[i] && separate_data[i] <= '9')
                {
                    char sprite_index = separate_data[i];
                    // AddNote(int col, int row, int num, int length, MusicDataOption option)
                    m_noteManager->AddNote(col, row, i, length, &m_options, sprite_index);
                }
            }
        }
    }
}
