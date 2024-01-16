import React from 'react'
import { MdCrib } from 'react-icons/md'
import { FaUserMd } from 'react-icons/fa'
import { Link, useNavigate, useLocation } from 'react-router-dom'
import { useAuth } from '../../contexts/AuthContext'

function Navbar() {
  const { currentUser, logout } = useAuth()
  console.log(currentUser)
  return (
    <nav className='navbar mb-12 shadow-lg bg-info text-info-content'>
      <div className='container mx-auto'>
        <div className='flex-none px-2 mx-2'>
          <MdCrib className='inline pr-2 text-5xl' />
          <Link to='/' className='text-lg font-bold align-middle'>
            Crib-Hunter
          </Link>
        </div>
        <div className='flex-1 px-2 mx-2'>
          <div className='flex justify-end'>
            <Link to='/' className='btn btn-ghost btn-sm rounded-btn'>
              Home
            </Link>
            <Link to='/profile' className='btn btn-ghost btn-sm rounded-btn'>
              Listing
            </Link>
            <Link
              to='/sell_listing'
              className='btn btn-ghost btn-sm rounded-btn'
            >
              Buy
            </Link>
            <Link
              to='/rent_listing'
              className='btn btn-ghost btn-sm rounded-btn'
            >
              Rent
            </Link>
            <div className='btn btn-ghost btn-sm rounded-btn'>
              <div className='dropdown dropdown-end'>
                <label tabIndex='0' className='btn btn-ghost btn-circle avatar'>
                  <div className='w-10'>
                    <FaUserMd className='text-2xl' />
                  </div>
                </label>
                <ul
                  tabIndex='0'
                  className='menu menu-compact dropdown-content mt-3 p-2 shadow bg-info'
                >
                  <li>
                    <div className='justify-between'>
                      <Link to={'/profile'}>Profile</Link>
                      <span className='badge'>New</span>
                    </div>
                  </li>
                  <li>
                    <a>Settings</a>
                  </li>
                  <li>
                    {currentUser ? (
                      <button
                        onClick={() => {
                          logout()
                        }}
                      >
                        <Link to={'/'}>Log Out</Link>
                      </button>
                    ) : (
                      <Link to={'/sign-in'}>Sign In</Link>
                    )}
                  </li>
                </ul>
              </div>
            </div>
          </div>
        </div>
      </div>
    </nav>
  )
}

export default Navbar
