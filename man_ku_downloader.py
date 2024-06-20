import os
import json
import time
import random
import requests
from bs4 import BeautifulSoup

chapter_json_name = 'chapter.json'

def random_sleep(mu=1, sigma=0.4):
    '''正态分布随机睡眠
    :param mu: 平均值
    :param sigma: 标准差，决定波动范围
    '''
    secs = random.normalvariate(mu, sigma)
    if secs <= 0:
        secs = mu  # 太小则重置为平均值
    print("sleep " + str(secs) + " seconds.")
    time.sleep(secs)

def get_chapter():
    url = "https://se8.us/index.php/api/comic/chapter?callback=jQuery22409696726926278845_1718370281236&mid=1767&_=1718370281237"
    r = requests.get(url)
    if r.status_code == 200:
        print("200")
        json_data = r.text
        with open('chapter_json.txt', 'w', encoding='utf-8') as f:
            f.write(json_data)
    

def read_json_from_file():
    with open(chapter_json_name, 'r', encoding='utf-8') as f:
        chapter_json = json.load(f)
        print(chapter_json)

def extract_name_and_link(data):
    results = []

    if isinstance(data, dict):
        result = {}
        for key, value in data.items():
            if key == 'name':
                result['name'] = value
            elif key == 'link':
                result['link'] = value
            else:
                results.extend(extract_name_and_link(value))
        if result:
            results.append(result)
    elif isinstance(data, list):
        for item in data:
            results.extend(extract_name_and_link(item))

    return results

def print_chapter():
    with open(chapter_json_name, 'r') as f:
        chapter_json = json.load(f)
        chapters = extract_name_and_link(chapter_json)
    for chapter in chapters:
        print(chapter['name'], chapter['link'])

def get_img_link(path, url):
    chapter_name = path.split('/')[1]
    print('downloading image links of ' + chapter_name)
    r = requests.get(url)
    html = r.text
    soup = BeautifulSoup(html, 'html.parser')
    img_tags = soup.find_all('img', class_='lazy-read')
    links = [img.get('data-original') for img in img_tags]
    f = open(path + '/link.txt', 'w')
    for img in img_tags:
        link = img.get('data-original')
        f.write(link + '\n')
    f.close()    

def download_img_links():
    with open(chapter_json_name, 'r') as f:
        chapter_json = json.load(f)
        chapters = extract_name_and_link(chapter_json)
    for chapter in chapters:
        chapter_name = chapter['name']
        chapter_link = chapter['link']
        full_path = 'image_link/' + chapter_name
        if not os.path.exists(full_path):
            os.mkdir(full_path)
            print("new folder: " + chapter_name)
        get_img_link(full_path, chapter_link)
        time.sleep(1)

def download_imgs():
    dir_list = os.listdir('./image_link')
    total_dir = len(dir_list)
    for dir in dir_list:
        path = 'image_link/' + dir
        file = path + '/link.txt'
        print(file)
        img_links = []
        with open(file, 'r') as f:
            for line in f:
                img_links.append(line.strip())
        i = 1
        for link in img_links:
            if link:
                r = requests.get(link)
                with open(path + '/' + str(i) + '.jpg', 'wb') as f:
                    print('downloding ' + path + '/' + str(i) + '.jpg')
                    f.write(r.content)
                i += 1
                
        random_sleep()

    
def list_dirs_in_directory(directory):
    return [f for f in os.listdir(directory) if os.path.isdir(os.path.join(directory, f))]

directory = './image_link'  # 替换为你的目录路径
dir_names = list_dirs_in_directory(directory)
unfinished = 0
for dir in dir_names:
    chapter_path = f"{directory}/{dir}"
    link_file = f"{chapter_path}/link.txt"
    file_list = [f for f in os.listdir(chapter_path) if os.path.isfile(os.path.join(chapter_path, f))]
    file_number = len(file_list)
    with open(link_file, 'r') as fi:
        line_number = sum(1 for line in fi)
    if file_number != line_number:
        print(f"file_number/line_number: {file_number}/{line_number} -- {dir}")
        unfinished += 1
print(f"unfinished: {unfinished}")