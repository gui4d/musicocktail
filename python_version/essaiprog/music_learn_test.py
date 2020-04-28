import numpy as np
from essentia.standard import *


music_path = "./audio/Muse_Uprising.wav"

msd_labels = ['rock','pop','alternative','indie','electronic','female vocalists','dance','00s','alternative rock','jazz','beautiful','metal','chillout','male vocalists','classic rock','soul','indie rock','Mellow','electronica','80s','folk','90s','chill','instrumental','punk','oldies','blues','hard rock','ambient','acoustic','experimental','female vocalist','guitar','Hip-Hop','70s','party','country','easy listening','sexy','catchy','funk','electro','heavy metal','Progressive rock','60s','rnb','indie pop','sad','House','happy']

# Our models take audio streams at 16kHz
sr = 16000

# Instantiate a MonoLoader and run it in the same line
audio = MonoLoader(filename=music_path, sampleRate=sr)()

# Instatiate the tagger and pass it the audio
predictions = TensorflowPredictMusiCNN(graphFilename='msd-musicnn.pb')(audio)

# Retrieve the top_n tags
top_n = 5

# Take advantage of NumPy to average and sort the predictions
for i, l in enumerate(np.mean(predictions, axis=0).argsort()[-top_n:][::-1], 1):
    print('{}: {}'.format(i, msd_labels[l]))



########################
######################### next one 


labels = ['classic', 'dance', 'hip hop', 'jazz',
          'pop', 'rnb', 'rock', 'speech']

sr = 16000
audio = MonoLoader(music_path, sampleRate=sr)()


predictions = TensorflowPredictVGGish(graphFilename='genre_electronic-vggish-audioset.pb')(audio)
predictions = np.mean(predictions, axis=0)
order = predictions.argsort()[::-1]
for i in order:
    print('{}: {:.3f}'.format(labels[i], predictions[i]))
