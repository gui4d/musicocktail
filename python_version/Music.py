import numpy as np
import matplotlib.pyplot as plt
import math
import matplotlib.pyplot as plt
import matplotlib.cm as cm
from datetime import date
import random

music_data = ['title',
              'album',
              'commentary',
              'author',
              'year',
              'file_path',
              'genre']
music_extractors = ['mtt_guitar',
                    'mtt_classical',
                    'mtt_slow',
                    'mtt_techno',
                    'mtt_strings ',
                    'mtt_drums ',
                    'mtt_electronic ',
                    'mtt_rock',
                    'mtt_fast',
                    'mtt_piano',
                    'mtt_ambient',
                    'mtt_beat',
                    'mtt_violin',
                    'mtt_vocal',
                    'mtt_synth',
                    'mtt_female',
                    'mtt_indian',
                    'mtt_opera',
                    'mtt_male',
                    'mtt_singing',
                    'mtt_vocals',
                    'mtt_no_vocals',
                    'mtt_harpsichord',
                    'mtt_loud',
                    'mtt_quiet',
                    'mtt_flute',
                    'mtt_woman',
                    'mtt_male_vocal',
                    'mtt_no_vocal',
                    'mtt_pop',
                    'mtt_soft',
                    'mtt_sitar',
                    'mtt_solo',
                    'mtt_man',
                    'mtt_classic',
                    'mtt_choir',
                    'mtt_voice',
                    'mtt_new age',
                    'mtt_dance',
                    'mtt_male voice',
                    'mtt_female vocal',
                    'mtt_beats',
                    'mtt_harp',
                    'mtt_cello',
                    'mtt_no voice',
                    'mtt_weird',
                    'mtt_country',
                    'mtt_metal',
                    'mtt_female_voice',
                    'mtt_choral',
                    'msd_rock',
                    'msd_pop',
                    'msd_alternative',
                    'msd_indie',
                    'msd_electronic',
                    'msd_female_vocalists',
                    'msd_dance',
                    'msd_00s',
                    'msd_alternative_rock',
                    'msd_jazz',
                    'msd_beautiful',
                    'msd_metal',
                    'msd_chillout',
                    'msd_male_vocalists',
                    'msd_classic_rock',
                    'msd_soul',
                    'msd_indie_rock',
                    'msd_Mellow',
                    'msd_electronica',
                    'msd_80s',
                    'msd_folk',
                    'msd_90s',
                    'msd_chill',
                    'msd_instrumental',
                    'msd_punk',
                    'msd_oldies',
                    'msd_blues',
                    'msd_hard_rock',
                    'msd_ambient',
                    'msd_acoustic',
                    'msd_experimental',
                    'msd_female_vocalist',
                    'msd_guitar',
                    'msd_Hip_Hop',
                    'msd_70s',
                    'msd_party',
                    'msd_country',
                    'msd_easy_listening',
                    'msd_sexy',
                    'msd_catchy',
                    'msd_funk',
                    'msd_electro',
                    'msd_heavy_metal',
                    'msd_Progressive_rock',
                    'msd_60s',
                    'msd_rnb',
                    'msd_indie_pop',
                    'msd_sad',
                    'msd_House',
                    'msd_happy',
                    'mood_happy',
                    'mood_sad',
                    'mood_danceable',
                    'mood_agressive',
                    'mood_party',
                    'mood_relaxed',
                    'mood_acoustic',
                    'scale_minor',
                    'scale_Major',
                    'key_A',
                    'key_B',
                    'key_C',
                    'key_D',
                    'key_E',
                    'key_F',
                    'key_G',
                    'key_AD',
                    'key_BD',
                    'key_CD',
                    'key_DD',
                    'key_ED',
                    'key_FD',
                    'key_GD',
                    'freq_440_classic',
                    'dormund_alternative',
                    'dormund_blues',
                    'dormund_electronic',
                    'dormund_folkcountry',
                    'dormund_funksoulrnb',
                    'dormund_jazz',
                    'dormund_pop',
                    'dormund_raphiphop',
                    'dormund_rock',
                    'electronic_ambient',
                    'electronic_dnb',
                    'electronic_house',
                    'electronic_techno',
                    'electronic_trance',
                    'rosamerica_cla',
                    'rosamerica_dan',
                    'rosamerica_hip',
                    'rosamerica_jaz',
                    'rosamerica_pop',
                    'rosamerica_rhy',
                    'rosamerica_roc',
                    'rosamerica_spe',
                    'tzanetakis_blu',
                    'tzanetakis_cla',
                    'tzanetakis_cou',
                    'tzanetakis_dis',
                    'tzanetakis_hip',
                    'tzanetakis_jaz',
                    'tzanetakis_met',
                    'tzanetakis_pop',
                    'tzanetakis_reg',
                    'tzanetakis_roc',
                    'instrument_acoustic',
                    'instrument_male',
                    'instrument_female',
                    'instrument_electronic',
                    'instrument_tonal',
                    'instrument_voice',
                    'instrument_instrumental']

class Music:
    def __init__(self):
        self.Id = 0
        self.Title=""
        self.Album=""
        self.Comentary=""
        self.Author=""
        self.Year=""
        self.File_path=""
        self.Genre=""
        self.Extractors_Name = music_extractors 
        self.Extractor_list_size = len(self.Extractors_Name)
        self.Extractors_Value = [ 0. for i in range(self.Extractor_list_size)]

    def Randomize_Extractors(self):
        for i in range(self.Extractor_list_size):
            self.Extractors_Value[i]= float(random.randint(0,100))/100.

    def Load_Extractors_From_Array(self,Extractors_Value):
        if (len(Extractors_Value)==self.Extractor_list_size) :
            for i in range(self.Extractor_list_size):
                self.Extractors_Value[i]= Extractors_Value[i]

    #function to export in database
    def Load_From_database(self,row):
        self.Id = int(row[0])
        self.Title= str(row[1])
        self.Album= str(row[2])
        self.Comentary= str(row[3])
        self.Author= str(row[4])
        self.Year= int(row[5])
        self.File_path= str(row[6])
        self.Genre= str(row[7])
        for i in range(self.Extractor_list_size):
            self.Extractors_Value[i]= float(row[i+8])

