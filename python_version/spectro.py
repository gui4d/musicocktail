
import librosa
import librosa.display
import wave
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import cm
from matplotlib.animation import FuncAnimation
from matplotlib.colors import ListedColormap, LinearSegmentedColormap     
from scipy.io import wavfile

manbo = './audio/mambo_no_5-lou_bega.wav'
muse = './audio/Muse_Uprising.wav'
# compute the log-mel spectrogram with librosa

def plot_spectro_librosa(file_name):
    audio, sr = librosa.load(file_name)
    audio_rep = librosa.feature.melspectrogram(y=audio, sr=sr).T
    plt.figure(figsize=(10, 4))
    audio_dB = librosa.power_to_db(audio_rep, ref=np.max)
    librosa.display.specshow(audio_dB, x_axis='time',
                         y_axis='mel', sr=sr,
                         fmax=8000)
    plt.colorbar(format='%+2.0f dB')
    plt.title('Mel-frequency spectrogram')
    plt.tight_layout()
    plt.show()

def plot_spectro_librosa2(file_name):
    n_fft = 2048
    hop_length = 512
    n_mels = 128
    audio, sr = librosa.load(file_name)
    S = librosa.feature.melspectrogram(audio, sr=sr, n_fft=n_fft, 
                                   hop_length=hop_length, 
                                   n_mels=n_mels)
    S_DB = librosa.power_to_db(S, ref=np.max)
    librosa.display.specshow(S_DB, sr=sr, hop_length=hop_length, 
                         x_axis='time', y_axis='cqt_hz');
    plt.colorbar(format='%+2.0f dB');
    plt.show()

def plot_spectro_mathplot(file_name):
    # Read the wav file (mono)
    obj = wave.open(file_name,'r')
    number_channel=obj.getnchannels()
    print( "Number of channels",number_channel)
    print ( "Sample width",obj.getsampwidth())
    print ( "Frame rate.",obj.getframerate())
    print ("Number of frames",obj.getnframes())
    print ( "parameters:",obj.getparams())
    obj.close()
    samplingFrequency, signalData = wavfile.read(file_name)
    if( number_channel > 1 ):
        signalData = signalData.sum(axis=1) / number_channel
    # Plot the signal read from wav file
    spec_plot= plt.figure()
    plt.title('Mel-frequency spectrogram')
    plt.specgram(signalData,Fs=samplingFrequency)
    plt.xlabel('Time')
    plt.ylabel('Frequency')
    #plt.yscale('log')
    plt.tight_layout()
    plt.show()

 

plot_spectro_librosa2(manbo)
plot_spectro_mathplot(manbo)
plot_spectro_librosa2(muse)
plot_spectro_mathplot(muse)








 

