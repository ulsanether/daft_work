import requests
import datetime



#api 파싱 주소
dust_url = "http://apis.data.go.kr/B552584/ArpltnInforInqireSvc/getMsrstnAcctoRltmMesureDnsty?"
weather_url = "http://apis.data.go.kr/1360000/VilageFcstInfoService_2.0/getUltraSrtNcst?"

#dust_apikey
service_key = "XIR%2F7enMmtb%2FRvXmb7Lrc0pZTegsHRd9xv%2Fo0D1j1efyfS%2FAt3u3wAxJ%2FHXLdTY%2B4VPHY%2FkOmEuH8KWmOu8x0A%3D%3D"

today = datetime.datetime.today()
base_date = today.strftime("%Y%m%d") # 
base_time = "0800" # 날씨 값

#울산 좌표값
nx = "102"
ny = "84"


data = dict()
data['date'] = base_date

weather_data = dict()

payload = "serviceKey=" + service_key + "&" +\
    "dataType=json" + "&" +\
    "base_date=" + base_date + "&" +\
    "base_time=" + base_time + "&" +\
    "nx=" + nx + "&" +\
    "ny=" + ny

res = requests.get(weather_url + payload)
items = res.json().get('response').get('body').get('items')

for item in items['item']:  #습도 데이터
   if item['category'] == 'T1H':
        weather_data = item['obsrValue']


   if item['category'] == 'REH':
        api_humidity = item['obsrValue']

search_condition = "WEEK"
stationName = "신정동"
payload1 = "serviceKey=" + service_key + "&" +\
    "returnType=json" + "&" +\
	"numOfRows=1" +"&"\
	"pageNo=1"+"&"\
    "stationName=" + stationName + "&" +\
    "dataTerm=DAILY" + "&" +\
    "ver=1.0"

res1 = requests.get(dust_url + payload1)
items1 = res1.json().get('response').get('body').get('items')
pm10_value= items1[0]['pm25Value']
pm25_value =items1[0]['pm10Value']