tmux new -s "REX" -d
tmux send-keys -t "REX" "fastapi run" C-m
tmux split-window -t "REX"
tmux send-keys -t "REX" "cd proj" C-m
tmux send-keys -t "REX" "npm run dev" C-m
