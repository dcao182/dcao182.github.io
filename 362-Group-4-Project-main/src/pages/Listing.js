import { useEffect, useState } from 'react'
import { useParams, Link } from 'react-router-dom'
import {
  collection,
  getDocs,
  query,
  where,
  orderBy,
  limit,
  startAfter,
} from 'firebase/firestore'
import { db } from '../firebase.config'
import { toast } from 'react-toastify'
import { useAuth } from '../contexts/AuthContext'
import SearchBox from '../components/SearchBox'
// import { SellListingItem } from "../components/SellListingItem";
// import "../fetchApi/fetchData";
function Listing({ listing_type }) {
  const { currentUser } = useAuth()
  const [listings, setListings] = useState(null)
  const [loading, setLoading] = useState(false)
  const [type, setType] = useState(listing_type)
  const [fullListings, setFullListings] = useState(null)
  const params = useParams()

  const fetchListings = async () => {
    try {
      const sellListings = collection(db, 'sell_listing')
      const sellQuery = query(
        sellListings,
        where('type', '==', type),
        // where('fullAddress', 'array-contains-any', []),
        orderBy('timestamp', 'desc')
        // limit(10)
      )
      const querySnap = await getDocs(sellQuery)
      let query_listings = []

      querySnap.forEach((doc) => {
        // console.log(doc.data())
        return query_listings.push({
          id: doc.id,
          data: doc.data(),
        })
      })
      setFullListings(query_listings)
      setListings(query_listings)
      setLoading(true)
    } catch (e) {
      toast.error(e.message)
    }
  }

  useEffect(() => {
    fetchListings()
  }, [type])

  const onBlurHandle = (e) => {
    console.log(fullListings)
    setListings(fullListings)
    let listing_filter
    if (e.target.value !== '') {
      listing_filter = listings.filter((element) =>
        element.data.fullAddress
          .toLowerCase()
          .includes(e.target.value.toLowerCase())
      )
      setListings(listing_filter)
    }

    // console.log(fullListings)
    console.log(listing_filter)
  }

  const onChangeHandle = (e) => {
    setListings(fullListings)
    let listing_filter
    if (e.target.value !== '') {
      listing_filter = listings.filter((element) =>
        element.data.fullAddress
          .toLowerCase()
          .includes(e.target.value.toLowerCase())
      )
      setListings(listing_filter)
    }
  }

  return !loading ? (
    <div>
      <SearchBox
        onChangeHandle={onChangeHandle}
        onBlurHandle={onBlurHandle}
      ></SearchBox>
      <h1>Is Loading...</h1>
    </div>
  ) : listings.length > 0 ? (
    <>
      <SearchBox
        onChangeHandle={onChangeHandle}
        onBlurHandle={onBlurHandle}
      ></SearchBox>
      <div className='mx-auto flex flex-col md:flex-row justify-center md:flex-wrap box-border'>
        {listings.map((listing) => {
          return (
            <div className='md:w-96 md:min-w-96 m-2'>
              <div
                key={listing.id}
                className='card card-side bg-base-100 shadow-xl items-stretch h-full'
              >
                <figure>
                  <img
                    src={
                      listing.data.imgUrls[0]
                        ? listing.data.imgUrls[0]
                        : listing.data.images
                    }
                    alt={'House For Sale'}
                  />
                </figure>
                <div className='card-body'>
                  <p className='card-title'>{listing.data.fullAddress}</p>
                  <h2>
                    $
                    {listing.data.price
                      .toString()
                      .replace(/\B(?=(\d{3})+(?!\d))/g, ',')}
                  </h2>
                  <Link to={`/listing/${listing.id}`}>
                    <div className='card-actions justify-end'>
                      <button className='btn btn-primary'>
                        {'Learn More'}
                      </button>
                    </div>
                  </Link>
                </div>
              </div>
            </div>
          )
        })}
      </div>
    </>
  ) : (
    <div>
      <SearchBox
        onChangeHandle={onChangeHandle}
        onBlurHandle={onBlurHandle}
      ></SearchBox>
      <p>No Listing for sales</p>
    </div>
  )
}
export default Listing
