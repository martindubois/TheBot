
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2022 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   TheBot
// File      front-end/src/pages/Layout.js

import { useEffect, useState } from 'react'
import { Outlet, Link } from 'react-router-dom'

const Layout = () =>
{
    const [ sBackEndVersion, SetBackEndVersion ] = useState( '' )

    const OnData = ( aData ) =>
    {
        SetBackEndVersion( aData.Version );
    }

    const OnError = () =>
    {
        SetBackEndVersion( 'ERROR' )
    }

    useEffect( () =>
    {
        fetch( 'http://127.0.0.1/GetVersion' )
            .then( ( aResponse ) => { return aResponse.json() } )
            .then( OnData )
            .catch( OnError )
    })

    return (
        <>
            <nav>
                <table>
                    <tbody>
                        <tr>
                            <td className = "Nav" ><Link to = "/"        >Camera  </Link></td>
                            <td className = "Nav" ><Link to = "/Map"     >Map     </Link></td>
                            <td className = "Nav" ><Link to = "/World"   >World   </Link></td>
                            <td className = "Nav" ><Link to = "/Tests"   >Tests   </Link></td>
                            <td className = "Nav" ><Link to = "/Settings">Settings</Link></td>
                        </tr>
                    </tbody>
                </table>
            </nav>

            <div className = "Main" >
                <Outlet />
            </div>

            <footer>
                <address>
                    Copyright &copy; 2022 KMS -
                    Back-end { sBackEndVersion } -
                    Front-end 0.0.0
                </address>
            </footer>
        </> )
};

export default Layout;
