import os
import sys
import shutil

def convert_single_file_gbk_to_utf8(file_path, backup_original=True):
    """
    转换单个GBK编码文件为UTF-8编码
    :param file_path: 待转换文件的路径
    :param backup_original: 是否备份原文件（备份文件后缀为.bak）
    :return: 转换成功返回True，失败返回False
    """
    # 检查文件是否存在
    if not os.path.exists(file_path):
        print(f"错误：文件 {file_path} 不存在")
        return False

    # 检查文件后缀是否为.h或.cpp
    file_ext = os.path.splitext(file_path)[1].lower()
    if file_ext not in ['.h', '.cpp']:
        print(f"跳过非目标文件：{file_path}（仅支持.h/.cpp文件）")
        return False

    try:
        # 1. 以GBK编码读取文件内容
        with open(file_path, 'r', encoding='gbk', errors='strict') as f:
            file_content = f.read()

        # 2. 备份原文件（如果开启备份）
        if backup_original:
            backup_file_path = f"{file_path}.bak"
            # 避免覆盖已存在的备份文件
            if not os.path.exists(backup_file_path):
                shutil.copy2(file_path, backup_file_path)
                print(f"已备份原文件：{backup_file_path}")
            else:
                print(f"备份文件已存在，跳过备份：{backup_file_path}")

        # 3. 以UTF-8编码写入原文件（覆盖原有内容）
        # 注意：C/C++文件一般不需要UTF-8 BOM，故使用纯utf-8编码（非utf-8-sig）
        with open(file_path, 'w', encoding='utf-8', errors='strict') as f:
            f.write(file_content)

        print(f"转换成功：{file_path}（GBK → UTF-8）")
        return True

    except UnicodeDecodeError:
        print(f"错误：文件 {file_path} 不是GBK编码，解码失败")
        return False
    except Exception as e:
        print(f"错误：转换文件 {file_path} 失败，异常信息：{str(e)}")
        return False

def convert_dir_gbk_to_utf8(dir_path, backup_original=True, recursive=True):
    """
    遍历目录（可选递归）转换所有.h/.cpp文件为UTF-8编码
    :param dir_path: 待遍历目录路径
    :param backup_original: 是否备份原文件
    :param recursive: 是否递归遍历子目录
    :return: 无返回值
    """
    # 检查目录是否存在
    if not os.path.isdir(dir_path):
        print(f"错误：目录 {dir_path} 不存在或不是有效目录")
        return

    # 遍历目录中的所有文件和子目录
    for root, dirs, files in os.walk(dir_path):
        for file_name in files:
            file_full_path = os.path.join(root, file_name)
            # 转换单个文件
            convert_single_file_gbk_to_utf8(file_full_path, backup_original)

        # 如果不开启递归，只遍历当前目录后退出
        if not recursive:
            break

def main():
    # 检查命令行参数
    if len(sys.argv) < 2:
        print("使用方法：")
        print("1. 转换单个文件：python gbk2utf8.py [文件路径]")
        print("2. 转换整个目录（递归）：python gbk2utf8.py [目录路径]")
        print("示例：")
        print("   python gbk2utf8.py D:\\code\\test.cpp")
        print("   python gbk2utf8.py D:\\code\\project")
        sys.exit(1)

    # 获取输入路径
    target_path = sys.argv[1]

    # 判断路径是文件还是目录
    if os.path.isfile(target_path):
        # 转换单个文件
        convert_single_file_gbk_to_utf8(target_path)
    elif os.path.isdir(target_path):
        # 转换整个目录
        convert_dir_gbk_to_utf8(target_path)
    else:
        print(f"错误：路径 {target_path} 既不是有效文件也不是有效目录")
        sys.exit(1)

if __name__ == "__main__":
    main()