# vortex-wargames

Solution to [level 0](https://overthewire.org/wargames/vortex/vortex0.html) from the OverTheWire hacking quest.

Just compile it like 
```bash
$ cc -o vortex vortex_level0.c
```
and then run it with the respective IP address and port:

```bash
$ ./vortex 176.9.9.172 5842
```
et voilà you'll get the credentials for the ssh server...

<dl>
  <dt>Note</dt>
  <dd>The executable takes the host's IP address <b>not</b> the host's name as the first parameter!</dd>
</dl>
