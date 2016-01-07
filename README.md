# lsmd

Suppose you have a directory with music in it.

````bash
$ ls music/chrono-resurrection/
Chrono Resurrection OST - 01 - A Premonition.m4a
Chrono Resurrection OST - 02 - Morning Sunlight.m4a
Chrono Resurrection OST - 03 - Peaceful Day.m4a
Chrono Resurrection OST - 04 - Goodnight.m4a
Chrono Resurrection OST - 05 - Secret of the Forest.m4a
Chrono Resurrection OST - 06 - Battle.m4a
Chrono Resurrection OST - 07 - Boss Battle Theme.m4a
Chrono Resurrection OST - 08 - Frog's Theme.m4a
Chrono Resurrection OST - 09 - Lucca's Fanfare Theme.m4a
Chrono Resurrection OST - 10 - The Day the World Revived.m4a
Chrono Resurrection OST - 11 - Robo's Theme.m4a
Chrono Resurrection OST - 12 - Battle 2 (Unreleased).m4a
Chrono Resurrection OST - 13 - The Brink of Time.m4a
Chrono Resurrection OST - 14 - Boss Battle Theme 2.m4a
Chrono Resurrection OST - 15 - Burn Bobunga.m4a
Chrono Resurrection OST - 16 - Magus' Theme.m4a
Chrono Resurrection OST - 17 - Singing Mountain.m4a
Chrono Resurrection OST - 18 - Corridors of Time.m4a
Chrono Resurrection OST - 19 - Zeal Palace.m4a
Chrono Resurrection OST - 20 - Schala's Theme.m4a
````

Then you can view the duration of each media file in minutes and
seconds. The output is slightly disingenuous, as audio files are not
printed in human-friendly order at the moment.

````bash
$ lsmd music/chrono-resurrection/
Chrono Resurrection OST - 01 - A Premonition.m4a                     2:03
Chrono Resurrection OST - 02 - Morning Sunlight.m4a                  0:39
Chrono Resurrection OST - 03 - Peaceful Day.m4a                      2:42
Chrono Resurrection OST - 04 - Goodnight.m4a                         0:10
Chrono Resurrection OST - 05 - Secret of the Forest.m4a              4:33
Chrono Resurrection OST - 06 - Battle.m4a                            1:40
Chrono Resurrection OST - 07 - Boss Battle Theme.m4a                 1:17
Chrono Resurrection OST - 08 - Frog's Theme.m4a                      2:50
Chrono Resurrection OST - 09 - Lucca's Fanfare Theme.m4a             0:44
Chrono Resurrection OST - 10 - The Day the World Revived.m4a         1:13
Chrono Resurrection OST - 11 - Robo's Theme.m4a                      1:24
Chrono Resurrection OST - 12 - Battle 2 (Unreleased).m4a             1:22
Chrono Resurrection OST - 13 - The Brink of Time.m4a                 2:34
Chrono Resurrection OST - 14 - Boss Battle Theme 2.m4a               2:34
Chrono Resurrection OST - 15 - Burn Bobunga.m4a                      1:39
Chrono Resurrection OST - 16 - Magus' Theme.m4a                      2:48
Chrono Resurrection OST - 17 - Singing Mountain.m4a                  3:21
Chrono Resurrection OST - 18 - Corridors of Time.m4a                 4:19
Chrono Resurrection OST - 19 - Zeal Palace.m4a                       4:07
Chrono Resurrection OST - 20 - Schala's Theme.m4a                    5:25
````

Alternatively, pass it a file.

````bash
$ lsmd music/cr/Chrono\ Resurrection\ OST\ -\ 01\ -\ A\ Premonition.m4a
Chrono Resurrection OST - 01 - A Premonition.m4a                     2:03
````

Build using:

````bash
$ git clone https://github.com/johnwalker/lsmd
$ cd lsmd && make
````

and place the resulting executable lsmd onto your $PATH.

# Dependencies

lsmd is tested only on Linux, but might work on Windows or
OSX. Patches for non-Unix systems won't be accepted unless they are
trivial.

+ libvlc