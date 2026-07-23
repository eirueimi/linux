#!/usr/bin/env bash
# 02-04 fork_counter チェッカー: /proc/fork_count が fork で増えるか
# （このカーネルをビルド→QEMU/実機で起動した環境で実行する）
set -u
[ -r /proc/fork_count ] || { echo "SKIP: /proc/fork_count がありません（改造カーネルで起動していない可能性）"; exit 2; }
before=$(cat /proc/fork_count)
for i in $(seq 1 20); do /bin/true; done   # 各 /bin/true は fork する
after=$(cat /proc/fork_count)
if [ "$after" -gt "$before" ]; then echo "PASS ($before -> $after)"; exit 0
else echo "FAIL: fork したのにカウンタが増えていません ($before -> $after)"; exit 1; fi
