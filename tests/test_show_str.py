from subprocess import run, PIPE
import shutil
import os
import pytest

B_FILE_PATH = './bin/show_str'
DATA_SAMPLES_DIR = './data-samples'
SAMPLE_DB_FILE_NAME = 'task007.db'
SAMPLE_DB_FILE_COPY = './tests/task007.db'

if os.path.isfile(B_FILE_PATH):

    def test_show_str_1():
        shutil.copy(SAMPLE_DB_FILE_COPY, os.path.join(DATA_SAMPLES_DIR, SAMPLE_DB_FILE_NAME))
        result = run([B_FILE_PATH], encoding='utf-8', stdout=PIPE)
        assert result.returncode == 0
        assert result.stdout.strip() == '7 Alexandr Kuricin 18 a.kuricin@yssu.ru'

if __name__ == '__main__':
    pytest.main()
