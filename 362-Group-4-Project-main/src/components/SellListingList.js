import React from "react";
import SellListingItem from "./SellListingItem";

const SellListingList = ({ sellListings }) => {
  return (
    <>
      <div className="container mx-auto flex justify-center gap-8 columns-4">
        {sellListings.map((listing) => {
          <div className="">
            <SellListingItem
              imageUrl={listing.data.imgUrl[0]}
              imageAlt={"House for Sale"}
              fullAddress={listing.data.fullAddress}
              price={listing.data.price}
              btnContent={"Learn More"}
              id={listing.id}
              key={listing.id}
            />
            ;
          </div>;
        })}
      </div>
    </>
  );
};

export default SellListingList;
