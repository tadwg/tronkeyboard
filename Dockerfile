FROM paijp/mplabx

COPY pic /root/

CMD cd /root/pic;make build
