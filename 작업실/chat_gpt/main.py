import requests
import io
import os
from google.oauth2 import service_account
from google.cloud import speech_v1p1beta1 as speech
from playsound import playsound

# 구글 클라우드 프로젝트 ID
project_id = "<your-project-id>"

# 구글 서비스 계정 키 파일 경로
key_file_path = "<your-key-file-path>"

# ChatGPT API 엔드포인트 URL
gpt_url = "https://api.openai.com/v1/engines/davinci-codex/completions"

# ChatGPT API 키
gpt_api_key = "<your-gpt-api-key>"

# 구글 음성인식 API 클라이언트
credentials = service_account.Credentials.from_service_account_file(
    key_file_path,
    scopes=["https://www.googleapis.com/auth/cloud-platform"],
)
client = speech.SpeechClient(credentials=credentials)


# 음성인식 함수
def transcribe_audio():
    # 오디오 파일 경로
    audio_file = "<your-audio-file-path>"

    # 오디오 파일 읽기
    with io.open(audio_file, "rb") as f:
        content = f.read()

    # 오디오 채널 설정
    audio = speech.RecognitionAudio(content=content)
    config = speech.RecognitionConfig(
        encoding=speech.RecognitionConfig.AudioEncoding.LINEAR16,
        sample_rate_hertz=16000,
        language_code="ko-KR",
        audio_channel_count=2,
    )

    # 오디오 전송 및 음성인식 결과 가져오기
    response = client.recognize(request={"config": config, "audio": audio})
    if len(response.results) > 0:
        transcript = response.results[0].alternatives[0].transcript
        return transcript
    else:
        return ""


# ChatGPT API 요청 함수
def query_gpt(text):
    response = requests.post(
        url=gpt_url,
        headers={
            "Content-Type": "application/json",
            "Authorization": f"Bearer {gpt_api_key}",
        },
        json={
            "prompt": text,
            "max_tokens": 50,
            "temperature": 0.7,
            "n": 1,
            "stop": None,
        },
    )
    if response.status_code == 200:
        response_data = response.json()
        output_text = response_data["choices"][0]["text"]
        return output_text
    else:
        return ""


# 메인 함수
def main():
    # 음성인식
    print("Listening...")
    text = transcribe_audio()
    print(f"You said: {text}")

    # ChatGPT API 요청
    print("Querying ChatGPT...")
    response_text = query_g
