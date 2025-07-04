import os
import re
from collections import *

BASE_DIR = os.path.dirname(__file__)
FILE_PATH = os.path.join(BASE_DIR, "Pink_Floyd_DB.txt")

def parse_database():
    albums = {}
    songs = {}
    current_album = None
    current_song_name = None
    current_lyrics_lines = []

    with open(FILE_PATH, encoding='utf-8') as file:
        for line in file:
            line = line.strip()

            if line.startswith("#"):
                if current_song_name and current_lyrics_lines:
                    songs[current_song_name]['lyrics'] = "\n".join(current_lyrics_lines)
                    current_lyrics_lines = []
                
                album_info = line[1:].split("::")[0]
                current_album = album_info.strip()
                albums[current_album] = []
                current_song_name = None
            
            elif line.startswith("*") and "::" in line:
                if current_song_name and current_lyrics_lines:
                    songs[current_song_name]['lyrics'] = "\n".join(current_lyrics_lines)
                    current_lyrics_lines = []
                parts = line[1:].split("::", 3)
                
                name = parts[0].strip()
                artist = parts[1].strip()
                length = parts[2].strip()
                initial_lyrics_part = parts[3].strip() if len(parts) > 3 else ""

                current_song_name = name 
                
                if current_album:
                    albums.setdefault(current_album, []).append(name)
                
                songs[name] = {
                    'album': current_album,
                    'length': length,
                    'lyrics': initial_lyrics_part 
                }
                if initial_lyrics_part:
                     current_lyrics_lines.append(initial_lyrics_part)
            elif line and current_song_name is not None:
                current_lyrics_lines.append(line)
        if current_song_name and current_lyrics_lines:
            songs[current_song_name]['lyrics'] = "\n".join(current_lyrics_lines)


    return albums, songs

def get_all_albums(albums, songs):
    return list(albums.keys())

def get_songs_in_album(albums, songs, album_name):
    return albums.get(album_name, [])

def get_song_length(albums, songs, song_name):
    return songs.get(song_name, {}).get('length')

def get_song_lyrics(albums, songs, song_name):
    song_data = songs.get(song_name)
    if song_data:
        return song_data.get('lyrics', 'Lyrics not found.')
    return 'Song not found.'

def get_album_by_song(albums, songs, song_name):
    return songs.get(song_name, {}).get('album')

def search_songs_by_title(albums, songs, text):
    text = text.lower()
    found_songs = [name for name in songs if text in name.lower()]
    return found_songs if found_songs else ['No songs found matching the name.']

def search_songs_by_lyrics(albums, songs, text):
    text = text.lower()
    found_songs = [name for name, data in songs.items() if 'lyrics' in data and text in data['lyrics'].lower()]
    return found_songs if found_songs else ['No songs found matching the lyrics.']