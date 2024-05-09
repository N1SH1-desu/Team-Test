#include "MusicData.h"
#include "./GameLib/game_lib.h"
#include "BreakObj.h"
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

void NoteManager::AddNote(int col, int row, int num, int length, MusicDataOption* p)
{
    Note note{};
    note.pos = 0.0f;
    note.perfect_pos = 60.0 * 4 * (row + (double)num / length) / p->bpm - p->offset;
    note.Flag = false;
    
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
        }
    }
}

void NoteManager::UpdateNotes(float current_time)
{
    for (auto& col : m_note_2d)
    {
        for (auto& row : col)
        {
            if (row.Flag)
            {
                row.pos = JUDGE_LINE - (JUDGE_LINE * (row.perfect_pos - current_time));

                if (WINDOW_H < row.pos && 0.3 < current_time - row.perfect_pos)
                {
                    row.Flag = false;

                }
            }
        }
    }
    JudgeFlag(current_time);
}

void NoteManager::JudgeFlag(float current_time)
{
    key_manager.Kye();

    for (auto& col : m_note_2d)
    {
        for (auto& row : col)
        {
            if (fabsf(row.perfect_pos - current_time) <= (0.2 / 2) && key_manager.GetKeyDown())
            {
                row.Flag = false;

            }
        }
    }

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
                GameLib::primitive::rect({ 400.0f * i, row.pos }, { 100.0f, 100.0f }, { 50.0f, 50.0f }, 0.0f,
                    { 0.0f, 1.0f, 0.0f, 1.0 });
            }
        }
   }

    GameLib::primitive::line({ 0.0f, JUDGE_LINE }, { 1280.0f, JUDGE_LINE }, { 1.0f, 1.0f, 1.0f, 1.0f });
}

double NoteManager::getNoteTiming(unsigned int col , unsigned int num)
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
    m_file.open(m_file_name, std::ios::in);
    if (!m_file)
    {
        return false;
    }
    string music_option_data;
    getline(m_file, music_option_data, ',');
    m_file_options << music_option_data;

    Load_MusicOptions();
    m_file.seekg(2, ios::cur);

    string music_notes;
    getline(m_file, music_notes, '.');
    m_file_data << music_notes;
    Load_NotesData();

    return true;
}

bool MusicData::GetFileData(const string& filename)
{
    m_file_name = filename;
    m_file.open(m_file_name, std::ios::in);
    string music_option_data;
    getline(m_file, music_option_data, ',');
    m_file_options << music_option_data;

    Load_MusicOptions();
    m_file.seekg(2, ios::cur);

    string music_notes;
    getline(m_file, music_notes, '.');
    m_file_data << music_notes;
    Load_NotesData();

    return true;
}

void MusicData::Load_MusicOptions()
{
    string row_str;
    while ( getline(m_file_options, row_str) )
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
                    // AddNote(int col, int row, int num, int length, MusicDataOption option)
                    m_noteManager->AddNote(col, row, i, length, &m_options);
                }
            }
        }
    }
}
