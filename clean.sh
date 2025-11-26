#!/usr/bin/env bash
set -ex

# -------------------------------------------------------
# 1. 安全检查：确保在一个 Git 仓库里
# -------------------------------------------------------
if ! git rev-parse --is-inside-work-tree >/dev/null 2>&1; then
    echo "❌ Not inside a Git repository!"
    exit 1
fi

# 当前分支
BRANCH=$(git symbolic-ref --short HEAD)
echo "Current branch: $BRANCH"

# -------------------------------------------------------
# 2. 确认提示（非常重要 + 防止误删）
# -------------------------------------------------------
echo "⚠️ WARNING: This script will do:"
echo "  • Remove local untracked files (git clean)"
echo "  • Remove local uncommitted changes (git reset --hard)"
echo "  • Sync to remote branch: origin/$BRANCH"
echo ""
read -p "Are you sure? (yes/no): " confirm
if [ "$confirm" != "yes" ]; then
    echo "❌ Cancelled."
    exit 1
fi

# -------------------------------------------------------
# 3. 清理未跟踪文件（慎重）
# -------------------------------------------------------
git clean -fdx   # -x 包含 .gitignore 里的文件

# -------------------------------------------------------
# 4. 丢弃本地修改
# -------------------------------------------------------
git reset --hard

# -------------------------------------------------------
# 5. 同步远端内容
# -------------------------------------------------------
git fetch origin

# -------------------------------------------------------
# 6. 强制让本地和远端对齐
# -------------------------------------------------------
git reset --hard origin/"$BRANCH"

echo "✨ Done. Local branch is now aligned with origin/$BRANCH"
