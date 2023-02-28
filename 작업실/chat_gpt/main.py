import pyaudio
from google.cloud import speech_v1p1beta1 as speech
from google.oauth2 import service_account
import os
import openai
import io
import sys
from google.cloud import texttospeech
import wave

# 인증 정보를 로드합니다.
sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8')
gpt_api_key = "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"
key_file_path = "chat-gpt-378811-6f49c9d46b3e.json"

openai.api_key =gpt_api_key

credentials = service_account.Credentials.from_service_account_file(key_file_path)

# 마이크에서 오디오 스트림을 가져옵니다.
p = pyaudio.PyAudio()
stream = p.open(format=pyaudio.paInt16, channels=1, rate=16000, input=True, frames_per_buffer=1024)

# Speech-to-Text API 클라이언트를 초기화합니다.
client = speech.SpeechClient(credentials=credentials)
texttospeech_client = texttospeech.TextToSpeechClient(credentials=credentials)
# 입력 받은 데이터를 저장할 리스트를 초기화합니다.
audio_data = []

try:
    # 10초간 오디오 데이터를 읽어옵니다.
    for i in range(0, int(16000 / 1024 * 5)):
        data = stream.read(1024)
        audio_data.append(data)

    # 오디오 데이터를 Speech-to-Text API로 변환합니다.
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
        # Speech-to-Text API에서 추출한 텍스트를 출력합니다.
        text = response.results[0].alternatives[0].transcript
        print(text)


    response_gpt = openai.Completion.create(
        model="text-davinci-003",
        prompt=text,
        temperature=0.7,
        max_tokens=1000,
        top_p=1,
        frequency_penalty=0,
        presence_penalty=0
    )
    print(response_gpt.choices[0].text)
    texttospeech_client = texttospeech.TextToSpeechClient(credentials=credentials)
    synthesis_input = texttospeech.SynthesisInput(text=response_gpt.choices[0].text)
    voice = texttospeech.VoiceSelectionParams(
          language_code="ko-KR",
    )
    audio_config = texttospeech.AudioConfig(
        audio_encoding=texttospeech.AudioEncoding.LINEAR16,
        speaking_rate=1.0,
        pitch=0.0,
        volume_gain_db=0.0,
        sample_rate_hertz=16000
    )
    response = texttospeech_client.synthesize_speech(
        input=synthesis_input, voice=voice, audio_config=audio_config
    )

finally:
    # 스트림을 닫아줍니다.
    stream.stop_stream()
    stream.close()
    p.terminate()


