mytrim() {
    local downloaded_file
    youtube-dl --extract-audio --embed-thumbnail --audio-format mp3 -o "%(title)s.%(ext)s" $1
    downloaded_file=$(youtube-dl --get-filename --extract-audio --embed-thumbnail --audio-format mp3 -o "%(title)s.%(ext)s" $1)
    ffmpeg -ss $2 -i "${downloaded_file}" -acodec copy -y temp.mp3
    mv temp.mp3 "${downloaded_file}"
}
mytrim $1 30