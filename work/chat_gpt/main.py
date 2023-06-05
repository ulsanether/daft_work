import pyaudio
from google.cloud import speech_v1p1beta1 as speech, texttospeech
from google.oauth2 import service_account
import os
import openai
import io
import sys
from gtts import gTTS
import playsound



sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8')
gpt_api_key = "################################t"
key_file_path = "#########.json"
openai.api_key =gpt_api_key
credentials = service_account.Credentials.from_service_account_file(key_file_path)
p = pyaudio.PyAudio()
stream = p.open(format=pyaudio.paInt16, channels=1, rate=16000, input=True, frames_per_buffer=1024)

client = speech.SpeechClient(credentials=credentials)
texttospeech_client = texttospeech.TextToSpeechClient(credentials=credentials)

audio_data = []


try:
    for i in range(0, int(16000 / 1024 * 4)):
        data = stream.read(1024)
        audio_data.append(data)
    audio = speech.RecognitionAudio(content=b"".join(audio_data))
    config = speech.RecognitionConfig(
        encoding=speech.RecognitionConfig.AudioEncoding.LINEAR16,
        sample_rate_hertz=16000,
        language_code="ko-KR",
        enable_word_time_offsets=True,
        enable_automatic_punctuation=True
    )
    response = client.recognize(config=config, audio=audio)
    if response.results:
        text = response.results[0].alternatives[0].transcript
        print(text)


    response = openai.ChatCompletion.create(
        model="gpt-3.5-turbo",
        messages=[
            {"role": "user", "content": text},
        ],
        temperature=0,
    )


    print(response['choices'][0]['message']['content'])
    tts = gTTS(response['choices'][0]['message']['content'], lang='ko')
    tts.save("response.mp3")
    playsound.playsound("response.mp3")
    os.remove("response.mp3")






finally:
    # 스트림을 닫아줍니다.
    stream.stop_stream()
    stream.close()
    p.terminate()




