from subprocess import run, PIPE
import os
import shutil
import pytest

B_FILE_PATH = './bin/real_db'
DATA_SAMPLES_DIR = './data-samples'
SAMPLE_DB_FILE_NAME = 'task007.db'
SAMPLE_DB_FILE_COPY = './tests/task007.db'

if os.path.isfile(B_FILE_PATH):
    shutil.copy(SAMPLE_DB_FILE_COPY, os.path.join(DATA_SAMPLES_DIR, SAMPLE_DB_FILE_NAME))

    def test_real_db_1():
        result = run([B_FILE_PATH], input='EXIT', encoding='utf-8', stdout=PIPE)
        assert result.returncode == 0
        assert result.stdout.strip() == ''
    
    def test_real_db_2():
        result = run([B_FILE_PATH], input='SHOW\n0\nEXIT', encoding='utf-8', stdout=PIPE)
        assert result.returncode == 0
        assert result.stdout.strip() == 'NO DATA'
    
    def test_real_db_3():
        result = run([B_FILE_PATH], input='SHOW\n345\nEXIT', encoding='utf-8', stdout=PIPE)
        assert result.returncode == 0
        assert result.stdout.strip() == 'NO DATA'
    
    def test_real_db_4():
        result = run([B_FILE_PATH], input='REMOVE\n2\nREMOVE\n3\nREMOVE\n4\nREMOVE\n5\nREMOVE\n6\nREMOVE\n7\nREMOVE\n8\nREMOVE\n9\nREMOVE\n10\nREMOVE\n11\nREMOVE\n12\nREMOVE\n13\nREMOVE\n14\nREMOVE\n15\nREMOVE\n16\nREMOVE\n17\nSHOWALL\nEXIT', encoding='utf-8', stdout=PIPE)
        assert result.returncode == 0
        assert result.stdout.strip() == '1 Alexandr Naumov 24 a.naumov@yssu.ru\n18 Nikolay Volkov 21 n.volkov@yssu.ru'
    
    def test_real_db_5():
        result = run([B_FILE_PATH], input='ADD\nBobr Kurwa 69 bobr@kurwa.pl\nSHOW\n19\nEXIT', encoding='utf-8', stdout=PIPE)
        assert result.returncode == 0
        assert result.stdout.strip() == '19 Bobr Kurwa 69 bobr@kurwa.pl'
    
    def test_real_db_6():
        result = run([B_FILE_PATH], input='ADD\nJamil Mardam Bay Hashim al-Atassi Nazim al-Kudsi 72 longname@example.net\nSHOW\n20\nEXIT', encoding='utf-8', stdout=PIPE)
        assert result.returncode == 0
        assert result.stdout.strip() == '20 Jamil Mardam Bay Hashim al-Atassi Nazim al-Kudsi 72 longname@example.net'
    
    def test_real_db_7():
        result = run([B_FILE_PATH], input='REMOVE\n888\nEXIT', encoding='utf-8', stdout=PIPE)
        assert result.returncode == 0
        assert result.stdout.strip() == ''
    
    def test_real_db_8():
        result = run([B_FILE_PATH], input='REMOVE\n888\nSHOWALL\nEXIT', encoding='utf-8', stdout=PIPE)
        assert result.returncode == 0
        assert result.stdout.strip() == '1 Alexandr Naumov 24 a.naumov@yssu.ru\n18 Nikolay Volkov 21 n.volkov@yssu.ru\n19 Bobr Kurwa 69 bobr@kurwa.pl\n20 Jamil Mardam Bay Hashim al-Atassi Nazim al-Kudsi 72 longname@example.net'
    
    def test_real_db_9():
        result = run([B_FILE_PATH], input='REMOVE\n20\nSHOWALL\nEXIT', encoding='utf-8', stdout=PIPE)
        assert result.returncode == 0
        assert result.stdout.strip() == '1 Alexandr Naumov 24 a.naumov@yssu.ru\n18 Nikolay Volkov 21 n.volkov@yssu.ru\n19 Bobr Kurwa 69 bobr@kurwa.pl'

if __name__ == '__main__':
    pytest.main()
