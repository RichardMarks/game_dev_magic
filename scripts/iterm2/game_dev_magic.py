#!/usr/bin/env python3.7

import iterm2

async def main(connection):
    app = await iterm2.async_get_app(connection)

    async def do_command(cmd):
        window = app.current_terminal_window
        if window is not None:
            session = app.current_terminal_window.current_tab.current_session
            await session.async_send_text(cmd)
    @iterm2.RPC
    async def do_clean_command():
        await do_command('./scripts/clean.sh\n')
    @iterm2.RPC
    async def do_build_command():
        await do_command('./scripts/build.sh\n')
    @iterm2.RPC
    async def do_run_command():
        await do_command('./scripts/run.sh\n')
    await do_clean_command.async_register(connection)
    await do_build_command.async_register(connection)
    await do_run_command.async_register(connection)
    
iterm2.run_forever(main)
